#include "testlib.h"
#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your remove seems to works for empty list, list with one element and with 3 elements.");
    test_plan(14);

    linkedlist list = {NULL};
    removeFirstEntryWithValue(&list, 0);
    test_equals_ptr((void*)list.head, (void*)NULL, "removed from empty list");

    entry *one = (entry*)malloc(sizeof(entry));
    one->next = one;
    one->prev = one;
    one->value = 1;

    list.head = one;
    removeFirstEntryWithValue(&list, 1);
    test_equals_ptr((void*)list.head, (void*)NULL, "removed from list wiht one element");

    entry *two = (entry*)malloc(sizeof(entry));
    entry *three = (entry*)malloc(sizeof(entry));
    entry *four = (entry*)malloc(sizeof(entry));
    two->next = three;
    three->next = four;
    four->next = two;
    two->prev = four;
    four->prev = three;
    three->prev = two;
    two->value = 2;
    three->value = 3;
    four->value = 4;
    // list: 2-3-4

    list.head = two;
    removeFirstEntryWithValue(&list, 4);
    // list: 2-3
    test_equals_ptr((void*)list.head, (void*)two, "list head points to entry with value 2");
    test_equals_ptr((void*)three->next, (void*)two, "removed last element in list, new last element has correct next");
    test_equals_ptr((void*)two->prev, (void*)three, "removed last element in list, head of list points to new last");

    entry *five = (entry*)malloc(sizeof(entry));
    five->value = 5;
    // list: 2-3-5
    five->prev = three;
    five->next = two;
    three->next = five;
    three->prev = two;
    two->prev = five;
    two->next = three;
    removeFirstEntryWithValue(&list, 2);
    // list: 3-5
    test_equals_ptr((void*)list.head, (void*)three, "removed first element, new head is element with value 3");
    test_equals_int(list.head->value, 3, "new head has actually value 3");
    test_equals_ptr((void*)three->prev, (void*)five, "removed first element, new head points to element with value 5");
    test_equals_ptr((void*)five->next, (void*)three, "removed first element, last element point to new head with value 3");

    entry *six = (entry*)malloc(sizeof(entry));
    six->value = 6;
    // list: 3-5-6
    six->prev = five;
    six->next = three;
    five->prev = three;
    five->next = six;
    three->prev = six;
    three->next = five;

    removeFirstEntryWithValue(&list, 5);
    // list: 3-6
    test_equals_ptr((void*)list.head, (void*)three, "removed middle element, head still is element with value 3");
    test_equals_ptr((void*)three->next, (void*)six, "removed middle element, head->next point to element with value 6");
    test_equals_ptr((void*)three->prev, (void*)six, "removed middle element, head->prev point to element with value 6");

    test_equals_ptr((void*)six->next, (void*)three, "removed middle element, last element with value 6 ->next points to head");
    test_equals_ptr((void*)six->prev, (void*)three, "removed middle element, last element with value 6 ->prev points to head");

    free(three);
    free(six);


    return test_end();
}


