#include "binarysearch.h"

/**
 * Compares two strings lexicographically.
 * Returns 0 if string1 and string2 are equal.
 * Returns < 0 if string1 comes lexicographically before string2.
 * Returns > 0 if string1 comes lexicographically after string2.
 */
int compareStrings(const char *string1, const char *string2) {
    int i = 0;
    
    while (string1[i] != '\0' && string1[i] == string2[i]) {
        i++;
    }
    
    return (unsigned char)string1[i] - (unsigned char)string2[i];
}

/**
 * Finds the index of a string in a lexicographically ascending array of strings with length numberOfStrings.
 * Returns -1 if the value to find string does not exist in the strings array.
 * Returns the index in the strings array where the value to find is.
 */ 
int binarySearch(const char *valueToFind, const char* strings[],  size_t numberOfStrings) {

    if (numberOfStrings <= 0) {
        return -1;
    }

    size_t left = 0;
    size_t right = numberOfStrings -1;

    while(left <= right) {
        size_t middle = left + (right - left) / 2;
        int cmp = compareStrings(valueToFind, strings[middle]);
        if (cmp == 0) { 
            return middle;

        } else if(cmp < 0) { //valuetofind comes before middle
            right = middle - 1;

        } else {
            left = middle + 1;
        }
    }
    return -1;
}
