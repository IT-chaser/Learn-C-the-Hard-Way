#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char src[4] = { 'a', 'a', 'a', '\0'};
    int i = 2;
    int *dest = &i;
    memcpy(dest, src, 4);
    printf("Copied string %d\n", *dest);
    return 0;
}