#include <stdio.h>

int main(int argc, char *argv[]) {
    int j = 24;
    int *i = &j;
    while (*i >= 0) {
        printf("%d\n", *i);
        *i--;
    }

    return 0;
}
