#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string) {
    *out_string = NULL; // Initialize output string pointer

    // Allocate initial memory for the string
    int buffer_size = 0;
    int index = 0;
    *out_string = calloc(1, 1); // Allocate memory for the null terminator
    check_mem(*out_string);

    while(1) {
        char ch = fgetc(stdin); // Read character from stdin

        if (ch == EOF || ch == '\n') {
            break; // Stop reading if end of file or newline is encountered
        }
        (*out_string)[index] = ch;
        index++;

        // Relocate the memory if needed
        if (index >= buffer_size) {
            buffer_size += MAX_DATA;
            *out_string = realloc(*out_string, buffer_size); // Resize the buffer
            check_mem(*out_string);
        }
    }

    (*out_string)[index] = '\0'; // Add null terminator to end the string

    return 0;

error:
    if (*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int *out_int) {
    char *input = NULL;
    int rc = read_string(&input);
    check(rc == 0, "Failed to read number.");

    *out_int = atoi(input);

    free(input);
    return 0;

error:
    if (input) free(input);
    return -1;
}

int read_scan(const char *fmt, ...) {
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;

    va_list argp;
    va_start(argp, fmt);

    for (i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            i++;
            switch (fmt[i]) {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;
                case 'd':
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int.");
                    break;

                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;  

                case 's':
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string);
                    check(rc == 0, "Failed to read string.");
                    break;

                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }

        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main(int argc, char *argv[]) {
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    printf("What is your first name? ");
    int rc = read_scan("%s", &first_name);
    check(rc == 0, "Failed to read first name.");

    printf("What is your initial? ");
    rc = read_scan("%c\n", &initial);
    check(rc == 0, "Failed initial.");

    printf("What is your last name? ");
    rc = read_scan("%s", &last_name);
    check(rc == 0, "Failed last name");

    printf("How old are you? ");
    rc = read_scan("%d", &age);

    printf("-----RESULTS-----\n");
    printf("First Name: %s", first_name);
    printf("Initial: '%c'\n", initial);
    printf("Last name: %s", last_name);
    printf("Age: %d\n", age);

    free(first_name);
    free(last_name);
    return 0;

error:
    return -1;
}