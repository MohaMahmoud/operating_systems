#include "insert.h"
#include "testlib.h"

#include <stdlib.h>

int main() {
	test_start("Your insert allocates a new array correctly.");
	test_plan(3);

	size_t capacity = 0;
	int *array = NULL;
	int *a = array;
	size_t len = 0;

	insert(&a, &len, &capacity, 42);

	test_assert(a != NULL, "pointer was updated");
	test_equals_int64(capacity, 10, "capacity is now 10");
	test_equals_int64(len, 1, "length is correct");

	free(a);
	return test_end();
}

