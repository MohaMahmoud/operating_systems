#include "testlib.h"
#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your insert, find and remove functions work for basic operations.");
    test_plan(12);

    linkedlist list = {NULL};
    test_equals_ptr((void*)findFirstEntryWithValue(&list, -1), (void*)NULL, "list is empty, it does not contain an entry with value -1");

    insertValue(&list, 42);
    insertValue(&list, 1);
    insertValue(&list, 2);
    insertValue(&list, 42);
    entry *fortytwo = findFirstEntryWithValue(&list, 42);
    test_equals_int(fortytwo->value, 42, "could find an entry with value 42");
    test_assert(fortytwo->next != NULL, "first element with vallue 42 has next");
    test_equals_int(fortytwo->next->value, 2, "first element with value 42 was inserted at cirrect position before element with value 2");
    test_assert(fortytwo->prev != NULL, "first element with vallue 42 has prev");
    test_equals_int(fortytwo->prev->value, 42, "first element with value 42 was inserted at cirrect position with prev pointing to the end of the list");

    removeFirstEntryWithValue(&list, 42);
    test_equals_int(list.head->value, 2, "after removing first element the new head is element with value 2");
    test_equals_int(findFirstEntryWithValue(&list, 42)->value, 42, "second entry with value 42 was not removed");

    removeFirstEntryWithValue(&list, 1);
    removeFirstEntryWithValue(&list, 42);

    entry *two = findFirstEntryWithValue(&list, 2);
    test_equals_ptr((void*)two, (void*)list.head, "list head and only element is the one with value 2");
    test_equals_ptr((void*)two->prev, (void*)two, "list head and only element prev points to itself");
    test_equals_ptr((void*)two->next, (void*)two, "list head and only element next points to itself");


    removeFirstEntryWithValue(&list, 2);
    test_equals_ptr((void*)list.head, (void*)NULL, "list does not contain any elements");




    return test_end();
}


