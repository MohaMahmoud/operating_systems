#include "insert.h"

#include <string.h>

/*
 * Reminder: insert() function from the tutorial that does not manage capacity.
 */
void insert_tut(int *a, size_t *length, int z)
{
	int *p = a;
	int *end = a + *length;
	while ((p < end) && (*p < z)) { ++p; }
	memmove(p + 1, p, (end - p) * sizeof(int));
	*p = z;
	(*length)++;
}

/*
 * New insert() function that reallocates if the array is full.
 */
void insert(int **array, size_t *length, size_t *capacity, int z)
{
	if (*length == *capacity) { 
		*capacity += 10; 
		int *new_array = (int*)malloc(*capacity * sizeof(int));
		if (new_array == NULL) return;
		for (size_t i = 0; i < *length; i++) {
			new_array[i] = (*array)[i];
		}
		free(*array);
		*array = new_array;
	}
	insert_tut(*array, length, z);
}
