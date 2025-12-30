/* Set SORT_ALGO to the sorting function. */
#define XSTR(X) STR(X)
#define STR(X) #X
#define SORT_ALGO_STR XSTR(SORT_ALGO)

#include "testlib.h"
#include "sorting.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Helper for testing: prints an array to a newly-allocated string. */
static char *asprint_array(int *a, size_t len)
{
    char *out = NULL;
    size_t size = 1, printed = 0;

    /* We need to format the whole array twice, first to determine the length
     * of the output string, then to actually print the data. We can avoid
     * copying code by using macros. */
#define COUNTING_PRINT(...) \
    do { \
        int n = snprintf(OUT, SIZE, __VA_ARGS__); \
        if (n < 0) { free(out); return NULL; } \
        COUNT += (size_t) n; \
    } while (0)

#define SPRINT_ARRAY \
    COUNTING_PRINT("{"); \
    for (size_t i = 0; i < len; i++) \
        COUNTING_PRINT(i == len-1 ? "%d}" : "%d, ", a[i]);

    /* These are substituted in COUNTING_PRINT above. */
#define SIZE 0
#define OUT NULL
#define COUNT size
    SPRINT_ARRAY;
#undef SIZE
#undef OUT
#undef COUNT

    out = malloc(size);
    if (out == NULL) return NULL;

#define SIZE (size - printed)
#define OUT (out + printed)
#define COUNT printed
    SPRINT_ARRAY;
#undef SIZE
#undef OUT
#undef COUNT

    return out;
#undef SPRINT_ARRAY
#undef COUNTING_PRINT
}

static int *copy_array(int *a, size_t len) {
    size_t sz_bytes = len * sizeof(int);
    int *clone = (int*)malloc(sz_bytes);
    if (!clone) {
        fprintf(stderr, "malloc failed!\n");
        return NULL;
    }

    memcpy(clone, a, sz_bytes);
    return clone;
}

static void test_array_sorted(int *original, int *supposedlySorted, size_t length, const char *algo)
{
    bool sorted = true;
    bool visitedInOriginal[length];
    memset(visitedInOriginal, false, length);
    for (size_t i = 0; i < length; ++i) {
        // see if element was actually in original
        bool foundInOriginal = false;
        for(size_t j = 0; j < length && foundInOriginal == false; ++j) {
            if(original[j] == supposedlySorted[i] && visitedInOriginal[j] == false) {
                foundInOriginal = true;
                visitedInOriginal[j] = true;
            }
        } 
        if(foundInOriginal == false) {
            sorted = false;
            test_failed_message("array contains element that is not in original array.");
            break;
        }

        if (i < length - 1 && supposedlySorted[i] > supposedlySorted[i + 1]) {
            sorted = false;
            break;
        }
    }
    char *after = asprint_array(supposedlySorted, length);
    size_t size = strlen(after) + strlen(algo) + 24;
    char *msg = malloc(size);
    snprintf(msg, size, "%s(array) = %s is sorted", algo, after);
    test_assert(sorted, msg);
    free(msg); free(after);
}


int main()
{
    test_start("Your " SORT_ALGO_STR " sorts our arrays.");
    test_plan(7);

    int sorted[4] = {1, 2, 3, 4};
    int *copy = copy_array(sorted, 4);
    SORT_ALGO(sorted, 4);
    test_array_sorted(copy, sorted, 4, "already sorted array: " SORT_ALGO_STR);
    free(copy);

    int reverse[5] = {5, 3, 2, 0, -1};
    copy = copy_array(reverse, 5);
    SORT_ALGO(reverse, 5);
    test_array_sorted(copy, reverse, 5, "array in reverse order: " SORT_ALGO_STR);
    free(copy);

    int oneElement[1] = {1};
    copy = copy_array(oneElement, 1);
    SORT_ALGO(oneElement, 1);
    test_array_sorted(copy, oneElement, 1, "array with one element: " SORT_ALGO_STR);
    free(copy);

    int largeElement[1] = {10000000};
    copy = copy_array(largeElement, 1);
    SORT_ALGO(largeElement, 1);
    test_array_sorted(copy, largeElement, 1, "array with one large number: " SORT_ALGO_STR);
    free(copy);

    int negativeNumbers[6] = {-1, -1, -5, -42, -1, -10};
    copy = copy_array(negativeNumbers, 6);
    SORT_ALGO(negativeNumbers, 6);
    test_array_sorted(copy, negativeNumbers, 6, "array with only negative numbers: " SORT_ALGO_STR);
    free(copy);

    int sameNumbers[3] = {0, 0, 0};
    copy = copy_array(sameNumbers, 3);
    SORT_ALGO(sameNumbers, 3);
    test_array_sorted(copy, sameNumbers, 3, "array with only the same numbers: " SORT_ALGO_STR);
    free(copy);

    int empty[0] = {};
    SORT_ALGO(empty, 0);
    test_assert(1, "does not crash with empty array");

    return test_end();
}
