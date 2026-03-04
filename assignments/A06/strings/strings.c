#include "strings.h"

/**
 * Returns the length of string s without counting the terminating null byte.
 */
size_t stringlength(const char *s)
{
    if (s == NULL) {return 0;}
    const char *current = s;
    while (*current != '\0') {
        current++;
    }

    return current - s;   
}

/**
 * Returns a new null byte terminated string that is the result of appending string s2 to s1.
 * The caller is responsible to free the returned string.
 * Returns NULL on any error.
 */
char *stringconcat(const char *s1, const char *s2)
{   

    size_t length1 = stringlength(s1);
    size_t length2 = stringlength(s2);
    size_t length3 = length1 + length2 + 1;
    char *s3 = (char*)malloc(length3);
    for (size_t i=0; i<length3; i++) {
        s3[i] = (i < length1) ? s1[i] : s2[i-length1];
    }
    s3[length3] = '\0';
    return s3;
}

/**
 * Splits string toSplit at every occurrence of the delimiter.
 * Returns a null-terminated array with pointers to the null-terminated
 * substrings. The caller should free the result by calling stringsplit_free().
 * Returns NULL on any error.
 */
char **stringsplit(const char *toSplit, char delimiter)
{   
    int delimeter_count = 0;
    size_t string_length = stringlength(toSplit);
    for (size_t i = 0; i<string_length; i++) {
        if (toSplit[i] == delimiter) {
            delimeter_count++;
        }
    }
    char **split_array = (char**)malloc((delimeter_count+2)*sizeof(char*));
    if (split_array == NULL) return NULL;

    int current = 0;
    const char *start = toSplit;
    const char *p = toSplit;
    while(*p!='\0') {
        if (*p == delimiter || *(p+1) == '\0') {
            size_t word_length = p-start; //size of word before
            split_array[current] = (char*)malloc(word_length + 1);
            
            for(size_t i=0; i < word_length; i++) {
                split_array[current][i] = start[i];
            }
            split_array[current][word_length] = '\0'; 

            current++;
            start = p + 1; 
        }
        p++;
    }
    return split_array;
}

/**
 * Frees the result from a stringsplit() call.
 */
void stringsplit_free(char **parts)
{
    if (parts == NULL) {
        return;
    }


    char **p = parts;
    while (*p != NULL) {
        free(*p); 
        p++;      
    }

    free(parts);
}
