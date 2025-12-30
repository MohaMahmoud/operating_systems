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
	test_start("Your insert puts new elements in the correct location.");
	test_plan(2);

	size_t capacity = 10;
	int *a = malloc(sizeof(int) * capacity);
	size_t len = 0;

	int to_insert[] = {15, 3, 8, -5, 0, 7, -100, 0, 33, 10};

	for (size_t i = 0; i < sizeof(to_insert)/sizeof(to_insert[0]); i++) {
		insert(&a, &len, &capacity, to_insert[i]);
	}

	test_equals_int64(len, 10, "length is correct");
	test_equals_string(debug_array_to_string(a, len), "-100 -5 0 0 3 7 8 10 15 33", "contents are correct");

	free(a);
	return test_end();
}
