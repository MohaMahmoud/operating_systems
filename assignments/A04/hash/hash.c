#include "hash.h"
#include <string.h>

/*
 * Returns a hash value for the given string.
 */
uint64_t hashString(char *c)
{
	int h0 = 5381;
	uint64_t current = h0;
	for (int i = 0; c[i] != '\0'; i++) {
		current = current * 33 + (int) c[i];
		}
	return (uint64_t) current;
}

/*
 * Inserts a key-value pair into the hash table.
 */
int insert(hashtable *table, char *key, int value)
{
    size_t start, pos;
    start = hashString(key) % table->capacity;
    pos = start;
    while (table->elements[pos].valid) {
        if (strcmp(key, table->elements[pos].key) == 0) {
            break;
        }
        // linear probing: skip valid elements
        pos = (pos + 1) % table->capacity;
        // if we come back to the start, there are no free slots
        if (pos == start) {
            return 0;
        }
    }
    table->elements[pos].valid = 1;
    table->elements[pos].key = key;
    table->elements[pos].value = value;
    return 1;
}

/*
 * Retrieves the value for a given key.
 */
int find(hashtable *table, char *key, int *value)
{
	(void) table; (void) key; (void) value;
	uint64_t start = hashString(key) % table->capacity;
	uint64_t pos = start;
	uint64_t occupied = table->elements[pos].valid;
	while (occupied) {
		if (strcmp(table->elements[pos].key, key) == 0) {
			*value = table->elements[pos].value;
			return 1;
		}
		pos = (pos + 1) % table->capacity;
		occupied = table->elements[pos].valid;
		if (pos == start) {
            break;
        }
	}
	return 0;
}

