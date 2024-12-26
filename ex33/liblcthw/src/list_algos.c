#include "lcthw/list_algos.h"
#include "lcthw/dbg.h"

inline void ListNode_swap(ListNode *a, ListNode *b) {
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp) {
    int sorted = 1;

    if (List_count(list) <= 1) {
        debug("List is empty or has one element, already sorted.");
        return 0; // already sorted
    }

    do {
        sorted = 1;
        LIST_FOREACH(list, first, next, cur) {
            if (cur->next) {
                debug("Comparing %s and %s", (char *)cur->value, (char *)cur->next->value);
                if (cmp(cur->value, cur->next->value) > 0) {
                    debug("Swapping %s and %s", (char *)cur->value, (char *)cur->next->value);
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    } while (!sorted);

    debug("List sorted successfully with bubble sort.");
    return 0;
}

inline List *List_merge(List *left, List *right, List_compare cmp) {
    List *result = List_create();
    void *val = NULL;

    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) {
            if (cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if (List_count(left) > 0) {
            val = List_shift(left);
            List_push(result,val);
        } else if (List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}

ListNode *List_split_in_half(List *list) {
    if (!list || !list->first) {
        return NULL; // Handle empty list
    }

    ListNode *slow = list->first;
    ListNode *fast = list->first;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

List *List_merge_in_place(List *left, List *right, List_compare cmp) {
    if (!left) return right;
    if (!right) return left;

    List result = {0};
    ListNode *cur_left = left->first;
    ListNode *cur_right = right->first;

    while (cur_left && cur_right) {
        if (cmp(cur_left->value, cur_right->value) <= 0) {
            List_push(&result, cur_left->value);
            cur_left = cur_left->next;
        } else {
            List_push(&result, cur_right->value);
            cur_right = cur_right->next;
        }
    }

    while (cur_left) {
        List_push(&result, cur_left->value);
        cur_left = cur_left->next;
    }

    while (cur_right) {
        List_push(&result, cur_right->value);
        cur_right = cur_right->next;
    }

    return &result;
}


List *List_merge_sort(List *list, List_compare cmp) {
    if (List_count(list) <= 1) {
        debug("List is empty or has one element, already sorted.");
        return list;
    }

    // Split the list into two halves
    ListNode *middle = List_split_in_half(list);
    List right_list;
    right_list.first = middle;
    right_list.last = list->last;
    right_list.count = List_count(list) / 2;

    list->last = middle->prev;
    if (list->last) {
    list->last->next = NULL; // Properly terminate the left list
    }
    list->count = List_count(list) - right_list.count;
    middle->prev = NULL;

    // Recursively sort the two halves
    List *sorted_left = List_merge_sort(list, cmp);
    List *sorted_right = List_merge_sort(&right_list, cmp);

    // Merge the two sorted halves
    return List_merge_in_place(sorted_left, sorted_right, cmp);
}
