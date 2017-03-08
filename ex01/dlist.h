#ifndef OS_EX01_TASK01_DLIST_H_
#define OS_EX01_TASK01_DLIST_H_

#include <stdbool.h>
#include <stdlib.h>

struct DList;
typedef struct DList DList;

struct DListNode;
typedef struct DListNode DListNode;

/* Allocate a new, empty list. */
DList* DList_new(void);

/* Allocate a new list, inserting each element of `arr`. */
DList* DList_from_array(const int arr[], size_t length);

/* Deallocate the list and all of its elements. */
void DList_delete(DList* list);

/* Print the list to standard output.
 *
 * Format:
 *   empty: []
 *   list with one element: [42]
 *   list with multiple elements: [1, 2, 3]
 */
void DList_print(const DList* list);

bool DList_is_empty(const DList* list);

/* Attaches a new node containing `value` to the end of the list. Returns true
 * on success and false on failure. */
bool DList_append(DList* list, int value);

/* Attaches a new node containing `value` to the beginning of the list. Returns
 * true on success and false on failure. */
bool DList_prepend(DList* list, int value);

/* Insert a new node containing `value` at position `index`. Returns true on
 * success and false on failure. */
bool DList_insert(DList* list, size_t index, int value);

/* Removes the element at position `index`, returning true on success and false
 * on failure. On success, the value stored in the removed node will be written
 * to `value` unless it's NULL. */
bool DList_remove(DList* list, size_t index, int* value);

/* Remove all elements from the list, resulting in an empty list. */
void DList_clear(DList* list);

/* Writes the value of the element at position `index` to `value`. Returns true
 * on success and false on failure. */
bool DList_get(const DList* list, size_t index, int* value);

/* Returns the number of elements in the list. */
size_t DList_length(const DList* list);

/* True if the list contains an element equal to `value`, false otherwise */
bool DList_contains(const DList* list, int value);

/* Search the list from front to back looking for `value`. If found, the
 * corresponding index is stored in `index` and true is returned. Otherwise
 * false is returned. */
bool DList_find(const DList* list, int value, size_t* index);

/* Same as DList_find, but searches from back to front. */
bool DList_find_last(const DList* list, int value, size_t* index);

/* Same as DList_find, but starts searching at index `from`. */
bool DList_find_from(const DList* list, int value, size_t from, size_t* index);

void DList_reverse(DList* list);

void DList_sort(DList* list);

#endif
