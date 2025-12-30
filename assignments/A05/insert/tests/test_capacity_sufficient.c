#include "insert.h"
#include "testlib.h"

#include <stdlib.h>

int main() {
	test_start("Your insert does not reallocate if the capacity is sufficient.");
	test_plan(3);

	size_t capacity = 5;
	int *array = malloc(sizeof(int) * capacity);
	int *a = array;
	size_t len = 0;

	for (size_t i = 0; i < capacity; i++) {
		insert(&a, &len, &capacity, i);
	}

	test_equals_ptr(a, array, "pointer is still the same");
	test_equals_int64(capacity, 5, "capacity is still the same");
	test_equals_int64(len, 5, "length is correct");

	free(array);
	return test_end();
}
