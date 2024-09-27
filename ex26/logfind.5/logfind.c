#define NDEBUG
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

const size_t MAX_LINE = 1024;

char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *) haystack;
    }
    for (; *haystack; ++haystack) {
        if (tolower(*haystack) == tolower(*needle)) {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n; ++h, ++n) {
                if (tolower((unsigned char)*h) != tolower((unsigned char)*n)) {
                    break;
                }
            }
            if (!*n) {
                return (char *)haystack;
            }
        }
    }
    return NULL;
}

int list_files(char ***files, int *count) {
    char *line = calloc(MAX_LINE, 1);
    FILE *file = fopen(".logfind", "r");
    int rc = -1;

    check(file, "Failed to open .logfind. Make that first.");
    check(files != NULL, "Invalid files array given.");
    check(count != NULL, "Invalid count pointer given.");

    while (fgets(line, MAX_LINE - 1, file) != NULL) {
        line[strlen(line) - 1] = '\0'; // drop the \n ending
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(".")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strcasestr(ent->d_name, line) != NULL) {
                    *files = realloc(*files, sizeof(char*) * (*count + 1));
                    check_mem(*files);
                    (*files)[*count] = strdup(ent->d_name);
                    check_mem((*files)[*count]);
                    (*count)++;
                }
            }
            closedir(dir);
        } else {
            check(0, "Could not open directory.");
        }
    }

    rc = 0; // all good

error:
    if (file) fclose(file);
    if (line) free(line);
    return rc;
}

int found_it(int use_or, int found_count, int search_len) {
    debug("use_or: %d, found_count: %d, search_len: %d", use_or, found_count, search_len);

    if (use_or && found_count > 0) {
        return 1;
    } else if (!use_or && found_count == search_len) {
        return 1;
    } else {
        return 0;
    }
}

int scan_file(const char *filename, int use_or, int search_len, char *search_for[]) {
    char *line = calloc(MAX_LINE, 1);
    FILE *file = fopen(filename, "r");
    int found_count = 0;
    int i = 0;

    check_mem(line);
    check(file, "Failed to open file: %s", filename);

    // read each line of the file and search that line for the contents
    while (fgets(line, MAX_LINE - 1, file) != NULL) {
        for (i = 0; i < search_len; i++) {
            if (strcasestr(line, search_for[i]) != NULL) {
                debug("file: %s, line: %s, search: %s", filename, line, search_for[i]);
                found_count++;
            }
        }

        if (found_it(use_or, found_count, search_len)) {
            printf("%s\n", filename);
            break;
        } else {
            found_count = 0;
        }
    }

    free(line);
    fclose(file);
    return 0;

error:
    if (line) free(line);
    if (file) fclose(file);

    return -1;
}

int parse_args(int *use_or, int *argc, char **argv[]) {
    (*argc)--;
    (*argv)++;

    if (strcmp((*argv)[0], "-o") == 0) {
        *use_or = 1;
        (*argc)--; // skip the -o
        (*argv)++;
        check(*argc > 1, "You need words after -o.");
    } else {
        *use_or = 0;
    }

    return 0;

error:
    return -1;
}

int main(int argc, char *argv[]) {
    int i = 0;
    int use_or = 0;
    char **files_found = NULL;
    int files_count = 0;

    check(argc > 1, "USAGE: logfind [-o] words");

    check(parse_args(&use_or, &argc, &argv) == 0, "USAGE: logfind [-o] words");

    check(list_files(&files_found, &files_count) == 0, "Failed to list files.");

    for (i = 0; i < files_count; i++) {
        scan_file(files_found[i], use_or, argc, argv);
        free(files_found[i]);
    }

    free(files_found);
    return 0;

error:
    if (files_found) {
        for (i = 0; i < files_count; i++) {
            if (files_found[i]) free(files_found[i]);
        }
        free(files_found);
    }
    return 1;
}
