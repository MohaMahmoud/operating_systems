#include "linkedlist.h"

/*
 * Creates a new entry with the given value.
 */
entry* allocateEntry(int value)
{
    (void) value;

    // TODO: Add code here.
    entry *new_node = (entry*) malloc(sizeof(entry));
    if (new_node == NULL) { return NULL; }
    (*new_node).value = value;
    new_node->next = NULL; 
    new_node->prev = NULL;
    return new_node;
}

/*
 * Release memory for an entry that is not used anymore.
 */
void freeEntry(entry *entry)
{
    // TODO: Add code here.
    if (entry->prev != NULL) {
        (*(*entry).prev).next = (*entry).next;
    }
    if (entry->next != NULL) {
        (*(*entry).next).prev = (*entry).prev;
    }
    free(entry);
}

/*
 * Insert value at the front of the list.
 */
void insertValue(linkedlist *list, int value)
{
    // TODO: Add code here.
    entry *new_node = allocateEntry(value);
    if (new_node == NULL) { return; }
    if (list->head != NULL) {
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    } else {
        list->head = new_node;
    }
}

/*
 * Find the first entry containing the value in the list.
 */
entry* findFirstEntryWithValue(linkedlist *list, int value)
{
    // TODO: Add code here.
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    entry *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
 * Remove the first entry containing the value from the list.
 */
void removeFirstEntryWithValue(linkedlist *list, int value)
{
    entry *entry = findFirstEntryWithValue(list, value);
    if (entry == NULL) {
        return;
    }

    if (entry->next == entry) {
        list->head = NULL;
    } else {
        entry->next->prev = entry->prev;
        entry->prev->next = entry->next;

        if (list->head == entry) {
            list->head = entry->next;
        }
    }
    freeEntry(entry);

}

