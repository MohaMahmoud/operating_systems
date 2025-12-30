#include "testlib.h"
#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>


void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size) {
	test_equals_int64(size, sizeof(entry), "malloc is called with the correct size");
	return __real_malloc(size);
}

int main()
{
    test_start("Your allocateEntry works.");


    test_plan(2);

    entry *entry = allocateEntry(42);

    test_equals_int(entry->value, 42, "your allocated entry contains value 42");

    free(entry);
    return test_end();
}


