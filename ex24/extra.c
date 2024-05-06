#include <stdio.h>
#include "dbg.h"

int scanfFunc(char *str, int size) {
    int rc = 0;
    char ch = '\0';
    int i = 0;

    for (i = 0; i < (size - 1); i++) {
        rc = scanf(" %c", &ch);
        if (ch == '\n' || ch == EOF || ch == '0'){
            break;
        }
        str[i] = ch;
    }
    str[i] = '\0';

    check(rc > 0, "Failed to read the character.");

    return 0;
error:

    return -1;   
}

int main(int argc, char *argv[]) {
    char first_name[50];
    char last_name[50];

    printf("-----To finish entering press 0 and click enter----\n");
    printf("Enter your first name: ");
    scanfFunc(first_name, sizeof(first_name));

    printf("Enter your last name: ");
    scanfFunc(last_name, sizeof(last_name));

    printf("First name: %s\n", first_name);
    printf("Last name: %s\n", last_name);

    return 0;
}