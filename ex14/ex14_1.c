#include <stdio.h>
#include <ctype.h>

void print_arguments(int argc, char *argv[]) {
    int i, j = 0;
    for (i = 0; i < argc; i++) {
        for (j = 0; argv[i][j] != '\0'; j++) {
            char ch = argv[i][j];
            if (isalpha(ch) || isblank(ch)) {
                printf("'%c' == %d ", ch, ch);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}