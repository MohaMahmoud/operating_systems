#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <stddef.h>

int compareStrings(const char *string1, const char *string2);
int binarySearch(const char *valueToFind, const char* strings[],  size_t numberOfStrings);

#endif
