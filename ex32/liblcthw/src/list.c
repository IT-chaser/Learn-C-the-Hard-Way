#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

// Helper function to verify list invariants
static inline void List_check_invariants(const List *list) {
    assert(list->count >= 0 && "List count must not be negative");
    if (list->count > 0) {
        assert(list->first != NULL && "List's first must not be NULL if count > 0");
        assert(list->last != NULL && "List's last must not be NULL if count > 0");
    } else {
        assert(list->first == NULL && "List's first must be NULL if count == 0");
        assert(list->last == NULL && "List's last must be NULL if count == 0");
    }
}

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list) {
    assert(list);
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }

        free(list->last);
        free(list);
    }
}

void List_clear(List *list) {
    assert(list);
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
    List_check_invariants(list);
}

void List_clear_destroy(List *list) {
    assert(list);
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        if (cur->prev) {
            free(cur->prev);
        }
        free(list->last);
        free(list);
    }
}

void List_push(List *list, void *value) {
    assert(list);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
    List_check_invariants(list);

error: 
    return;
}

void *List_pop(List *list) {
    assert(list);
    ListNode *node = list->last;
    void *result = node != NULL ? List_remove(list, node) : NULL;
    List_check_invariants(list);
    return result;
}

void List_unshift(List *list, void *value) {
    assert(list);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;
    List_check_invariants(list);

error: 
    return;
}

void *List_shift(List *list) {
    assert(list);
    ListNode *node = list->first;
    void *result = node != NULL ? List_remove(list, node) : NULL;
    List_check_invariants(list);
    return result;
}

void *List_remove(List *list, ListNode *node) {
    assert(list);
    assert(node);
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL.");

    if (list->first == node && list->last == node) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

    List_check_invariants(list);

error: 
    return result;
}