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
    DIR *d;
    struct dirent *dir;
    int capacity = 10;
    int file_count = 0;
    char **file_list = malloc(capacity * sizeof(char*));

    check_mem(file_list);

    d = opendir(".");
    check(d != NULL, "Failed to open current directory.");

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }
        if (strcasecmp(dir->d_name, ".h") || strcasecmp(dir->d_name, ".")) {
            if (file_count >= capacity) {
                capacity *= 2;
                file_list = realloc(file_list, capacity * sizeof(char*));
                check_mem(file_list);
            }
            file_list[file_count] = strdup(dir->d_name);
            check_mem(file_list[file_count]);
            file_count++;
        }
    }
    
    closedir(d);

    *files = file_list;
    *count = file_count;
    return 0;

error:
    if (file_list) {
        for (int i = 0; i < file_count; i++) {
            if (file_list[i]) free(file_list[i]);
        }
        free(file_list);
    }
    if (d) closedir(d);
    return -1;
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
    char **files_found;
    int files_count;

    check(argc > 1, "USAGE: logfind word word word");

    check(list_files(&files_found, &files_count) == 0, "Failed to list files.");

    for(i = 0; i < files_count; i++) {
        scan_file(files_found[i], argc, argv);
        free(files_found[i]);
    }

    free(files_found);
    return 0;

error:
    return 1;
}