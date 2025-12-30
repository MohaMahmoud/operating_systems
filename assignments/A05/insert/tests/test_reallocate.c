#include "insert.h"
#include "testlib.h"

#include <stdio.h>
#include <stdlib.h>

char *debug_array_to_string(int *a, size_t len)
{
	static char buf[100];
	size_t written = 0;
	for (size_t i = 0; i < len && written < sizeof(buf) - 1; i++) {
		written += snprintf(buf + written, sizeof(buf) - written, "%d ", a[i]);
	}
	if (written > 0 && buf[written - 1] == ' ') {
		buf[written - 1] = 0;
	}
	return buf;
}

int main() {
	test_start("Your insert reallocates if the buffer is not large enough.");
	test_plan(3);

	size_t capacity = 16;
	int *array = malloc(sizeof(int) * capacity);
	int *a = array;
	size_t len = 16;

	for (size_t i = 0; i < len; i++) {
		a[i] = i;
	}

	insert(&a, &len, &capacity, -1);

	test_equals_int64(capacity, 26, "capacity is now 26");
	test_equals_int64(len, 17, "length is correct");
	test_equals_string(debug_array_to_string(a, len), "-1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15", "array contents are correct");

	free(a);
	return test_end();
}

