#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb) (int a, int b);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
*/
int *bubble_sort(int *numbers, int count, compare_cb cmp) {
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target)
        die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; i++) {
        for (j = 0; j < count - 1; j++) {
            if (cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}
int sorted_order(int a, int b) {
    return a - b;
}

int reverse_order(int a, int b) {
    return b - a;
}

int strange_order(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

int *new_sort(int *numbers, int count, char *sort_type) {
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target2 = malloc(count * sizeof(int));
    if (!target2) 
        die("Memory error.");

    memcpy(target2, numbers, count * sizeof(int));
    if (strcmp(sort_type, "sorted") == 0){
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - 1; j++) {
                if (sorted_order(target2[j], target2[j + 1]) > 0) {
                    temp = target2[j + 1];
                    target2[j + 1] = target2[j];
                    target2[j] = temp;
                }
            }
        }
    } else if (strcmp(sort_type, "reverse") == 0){
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - 1; j++) {
                if (reverse_order(target2[j], target2[j + 1]) > 0) {
                    temp = target2[j + 1];
                    target2[j + 1] = target2[j];
                    target2[j] = temp;
                }
            }
        }
    } else if (strcmp(sort_type, "strange") == 0){
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - 1; j++) {
                if (strange_order(target2[j], target2[j + 1]) > 0) {
                    temp = target2[j + 1];
                    target2[j + 1] = target2[j];
                    target2[j] = temp;
                }
            }
        }
    } else {
        die ("Sort function not called properly");
    }
    return target2;
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
*/
void test_sorting(int *numbers, int count, compare_cb cmp, char *sort_type) {
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);
    int *sorted2 = new_sort(numbers, count, sort_type);

    if (!sorted)
        die("Failed to sort as requested.");
    if (!sorted2)
        die("Failed to sort as requested.");

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("Normal sorting algorithm:\n");

    for (i = 0; i < count; i++) {
        printf("%d ", sorted2[i]);
    }
    printf("\n");

    free(sorted);
    free(sorted2);

    // unsigned char *data = (unsigned char *) cmp;
    // for(i = 0; i < 25; i++) {
    //     printf("%02x:", data[i]);
    // }
    // printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) die("USAGE: ex18 4 5 2 1 6 8");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error.");

    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order, "sorted");
    test_sorting(numbers, count, reverse_order, "reverse");
    test_sorting(numbers, count, strange_order, "strange");

    free(numbers);

    return 0;
}