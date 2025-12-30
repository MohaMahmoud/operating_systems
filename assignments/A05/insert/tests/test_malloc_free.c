#include "insert.h"
#include "testlib.h"

#include <stdlib.h>

static int *array, *array_new;

void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size) {
	test_equals_int64(size, sizeof(int) * 26, "malloc is called with the correct size");
	array_new = __real_malloc(size);
	return array_new;
}

void __wrap_free(void *ptr) {
	test_equals_ptr(ptr, array, "free is called with the original array");
	__real_free(ptr);
}

int main() {
	test_start("Your insert uses malloc and free to reallocate the array.");
	test_plan(3);

	size_t capacity = 16;
	array = __real_malloc(sizeof(int) * capacity);
	int *a = array;
	size_t len = 16;

	for (size_t i = 0; i < len; i++) {
		a[i] = i;
	}

	insert(&a, &len, &capacity, -1);

	test_equals_ptr(a, array_new, "array pointer is updated with result from malloc");

	__real_free(a);
	return test_end();
}

