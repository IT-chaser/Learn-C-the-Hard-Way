#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

/**
 * @brief Represents a node in a doubly-linked list.
 */
struct ListNode;
typedef struct ListNode {
    struct ListNode *prev; /**< Pointer to the previous node in the list */
    struct ListNode *next; /**< Pointer to the next node in the list */
    void *value;           /**< Pointer to the value stored in the node */
} ListNode;

/**
 * @brief Represents a doubly-linked list.
 */
typedef struct List {
    int count;             /**< Number of nodes in the list */
    ListNode *first;       /**< Pointer to the first node in the list */
    ListNode *last;        /**< Pointer to the last node in the list */
} List;

/**
 * @brief Creates a new, empty list.
 *
 * @return Pointer to the newly created list.
 */
List *List_create();

/**
 * @brief Destroys a list, freeing all nodes but not the values.
 *
 * @param list Pointer to the list to destroy.
 */
void List_destroy(List *list);

/**
 * @brief Clears all values in the list without destroying the list itself.
 *
 * @param list Pointer to the list to clear.
 */
void List_clear(List *list);

/**
 * @brief Clears all values in the list and destroys the list itself.
 *
 * @param list Pointer to the list to clear and destroy.
 */
void List_clear_destroy(List *list);

/**
 * @brief Macro to get the count of nodes in a list.
 *
 * @param A Pointer to the list.
 * @return The count of nodes in the list.
 */
#define List_count(A)  ((A)->count)

/**
 * @brief Macro to get the value of the first node in a list.
 *
 * @param A Pointer to the list.
 * @return Value of the first node, or NULL if the list is empty.
 */
#define List_first(A)  ((A)->first != NULL ? (A)->first->value : NULL)

/**
 * @brief Macro to get the value of the last node in a list.
 *
 * @param A Pointer to the list.
 * @return Value of the last node, or NULL if the list is empty.
 */
#define List_last(A)  ((A)->last != NULL ? (A)->last->value : NULL)

/**
 * @brief Adds a value to the end of the list.
 *
 * @param list Pointer to the list.
 * @param value Pointer to the value to add.
 */
void List_push(List *list, void *value);

/**
 * @brief Removes and returns the value at the end of the list.
 *
 * @param list Pointer to the list.
 * @return Pointer to the value removed, or NULL if the list is empty.
 */
void *List_pop(List *list);

/**
 * @brief Adds a value to the beginning of the list.
 *
 * @param list Pointer to the list.
 * @param value Pointer to the value to add.
 */
void List_unshift(List *list, void *value);

/**
 * @brief Removes and returns the value at the beginning of the list.
 *
 * @param list Pointer to the list.
 * @return Pointer to the value removed, or NULL if the list is empty.
 */
void *List_shift(List *list);

/**
 * @brief Removes a specific node from the list.
 *
 * @param list Pointer to the list.
 * @param node Pointer to the node to remove.
 * @return Pointer to the value stored in the removed node.
 */
void *List_remove(List *list, ListNode *node);

/**
 * @brief Macro to iterate over a list.
 *
 * @param L Pointer to the list to iterate over.
 * @param S Starting node (e.g., `first` or `last`).
 * @param M Movement direction (e.g., `next` or `prev`).
 * @param V Variable to hold the current node during iteration.
 */
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; \
                                 ListNode *V = NULL;    \
                                 for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
