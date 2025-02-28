#include <assert.h>
#include <string.h>

#include "minunit.h"
#include "../src/lcthw/list_algos.h"

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

#define NUM_VALUES 5

List *create_words() {
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words) {
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort() {
    List *words = create_words();

    // Should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on already sorted list
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on empty list
    words = List_create();
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort() {
    List *words = create_words();

    debug("Original list:");
    {
        LIST_FOREACH(words, first, next, cur) {
            if (cur->value) {
                debug("%s", (char *)cur->value);
            } else {
                debug("Invalid value in node");
            }
        }
    }

    List *sorted = List_merge_sort(words, (List_compare) strcmp);

    debug("Sorted list:");
    {
        LIST_FOREACH(sorted, first, next, cur) {
            if (cur->value) {
                debug("%s", (char *)cur->value);
            } else {
                debug("Invalid value in node");
            }
        }
    }

    mu_assert(is_sorted(sorted), "Merge sort failed.");

    List_destroy(sorted);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);