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
    FILE *file = fopen(".logfind", "r");
    char line[MAX_LINE];
    int rc = -1;

    check(file, "Failed to open .logfind. Make that first.");
    check(files != NULL, "Invalid files array given.");
    check(count != NULL, "Invalid count pointer given.");

    while(fgets(line, MAX_LINE-1, file) != NULL) {
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
    return rc;
}

int scan_file(const char *filename, int search_len, char *search_for[]) {
    char *line = calloc(MAX_LINE, 1);
    FILE *file = fopen(filename, "r");
    char *found = NULL;
    int i = 0;

    check_mem(line);
    check(file, "Failed to open file: %s", filename);

    // read each line of the file and search that line for the contents
    while(fgets(line, MAX_LINE-1, file) != NULL && found == NULL) {
        for(i = 0; i < search_len && found == NULL; i++) {
            found = strcasestr(line, search_for[i]);
            if(found) {
                printf("%s\n", filename);
            }
        }
    }

    free(line);
    fclose(file);
    return 0;

error:
    if(line) free(line);
    if(file) fclose(file);

    return -1;
}

int main(int argc, char *argv[]) {
    int i = 0;
    char **files_found = NULL;
    int files_count = 0;
    check(argc > 1, "USAGE: logfind word word word");

    check(list_files(&files_found, &files_count) == 0, "Failed to list files.");

    for(i = 0; i < files_count; i++) {
        scan_file(files_found[i], argc, argv);
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
