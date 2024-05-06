#include <stdio.h>

#define CASES_8(start, num) \
    case start: \
    case start + 1: \
    num = num + 1; \
    case start + 2: \
    num = num + 1; \
    case start + 3: \
    num = num + 1; \
    case start + 4: \
    num = num + 1; \
    case start + 5: \
    num = num + 1; \
    case start + 6: \
    num = num + 1; \
    case start + 7: \
    num = num + 1; 

#define CASES_32(start, num) \
    CASES_8(start, num) \
    CASES_8((start + 8), num) \
    CASES_8((start + 16), num) \
    CASES_8((start + 24), num)

int main(int argc, char *argv[]) {
    int value = 15; // Example value
    int i = 0;
    switch (value) {
        CASES_32(0, i) // Generate 32 case statements starting from 0
        {
            // Code for each case
            i++;
            printf("Value is within the range of 0 to 31 and i is: %d\n", i);
            break;
        }
        default:
            printf("Value is out of range\n");
            break;
    }

    return 0;
}