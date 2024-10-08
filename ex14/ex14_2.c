#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[], int len);

void print_arguments(int argc, char *argv[]) {
    int i = 0;
    for (i = 0; i < argc; i++) {
        int length = strlen(argv[i]);
        print_letters(argv[i], length);
    }
}

void print_letters(char arg[], int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        if (isdigit(arg[i])) {
            printf("digits: %c ", arg[i]);
        }
        char ch = arg[i];
        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        } 
    }

    printf("\n");
}

int can_print_it(char ch) {
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}