#include "testlib.h"
#include <stdlib.h>
#include "linkedlist.h"

static void* entryToTest;

void __real_free(void *ptr);

void __wrap_free(void *ptr) {
	test_equals_ptr(ptr, entryToTest, "free is called with the pointer to the entry");
	__real_free(ptr);
}

int main() {
	test_start("Your freeEntry uses free correctly.");
	test_plan(1);

    entryToTest = (void*)malloc(sizeof(entry));

    freeEntry((entry*) entryToTest);

	return test_end();
}

