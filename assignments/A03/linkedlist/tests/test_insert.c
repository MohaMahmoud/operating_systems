#include "testlib.h"
#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your insert seems to work.");
    test_plan(6);

    linkedlist list = {NULL};
    insertValue(&list, 1);
    test_equals_int(list.head->value, 1, "could insert value 1 as first element");

    insertValue(&list, 2);
    test_equals_int(list.head->value, 2, "could insert value 2 at front of existing list");
    test_equals_int(list.head->next->value, 1, "second entry in list is the one with value 1");
    test_equals_int(list.head->prev->value, 1, "second entry in list is the one with value 1");

    test_equals_ptr((void*)list.head->next->next, (void*)list.head, "second entry in list with value 1 next points to list head");
    test_equals_ptr((void*)list.head->next->prev, (void*)list.head, "second entry in list with value 1 prev points to list head");



    return test_end();
}


