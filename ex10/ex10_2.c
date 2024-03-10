#include <stdio.h>

int main(int argc, char *argv[]) {
    // if (argc != 2) {
        // printf("ERROR: You need one argument.\n");
        // this is how you abort program
        // return 1;
    // }

    int i, j = 0;
    for (j = 1; j < argc; j++) {
        for (i = 0; argv[j][i] != '\0'; i++) {
            char letter = argv[j][i];
            if (letter >= 'A' && letter <= 'Z') {
                letter += 32;
            }
            if (letter == 'a') {
                printf("%d: 'a'\n", i);
            } else if (letter == 'e') {
                printf("%d: 'e'\n", i);
            } else if (letter == 'i') {
                printf("%d: 'i'\n", i);
            } else if (letter == 'o') {
                printf("%d: 'o'\n", i);
            } else if (letter == 'u') {
                printf("%d: 'u'\n", i);
            } else if (letter == 'y') {
                if (i > 2) {
                        // it's only sometimes Y
                        printf("%d: 'y'\n", i);
                    }
            } else {
                printf("%d: %c is not a vowel\n", i, letter);
            }
        }
    }
    return 0;
}