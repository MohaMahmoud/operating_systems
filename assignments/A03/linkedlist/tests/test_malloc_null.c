#include "testlib.h"
#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>


void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size) {
    (void)size;
	return (void*)NULL;
}

int main()
{
    test_start("You check whether malloc could allocate the memory before using it.");


    test_plan(4);
    entry *firstEntry = __real_malloc(sizeof(entry));
    firstEntry->value = 0;
    firstEntry->prev = firstEntry;
    firstEntry->next = firstEntry;
    linkedlist list = {firstEntry};

    insertValue(&list, 1);
    test_equals_ptr((void*)list.head, (void*)firstEntry, "list still contains first entry with value 0");
    test_equals_ptr((void*)firstEntry->prev, (void*)firstEntry, "list contains first entry with value 0 and its prev points to itself");
    test_equals_ptr((void*)firstEntry->next, (void*)firstEntry, "list only contains first entry with value 0, because its next points to itself as well");
    test_equals_int(list.head->value, 0, "value of first and only entry is truly 0");

    free(firstEntry);
    return test_end();
}


