#include "testlib.h"
#include "pointers.h"

#include "stddef.h"

#define ARRAY_SIZE(element) (sizeof(element) / sizeof(*(element)))

int main()
{
    test_start("You calculate correct averages with indirection.");
    test_plan(4);

    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int small[] = {1, 2};

    int *array_indirect[ARRAY_SIZE(array)] = {0};
    int *small_indirect[ARRAY_SIZE(small)] = {0};
    int *array_indirect_skip[ARRAY_SIZE(array) / 3] = {0};
    for (unsigned i = 0; i < ARRAY_SIZE(array); ++i)
        array_indirect[i] = array + i;
    for (unsigned i = 0; i < ARRAY_SIZE(small); ++i)
        small_indirect[i] = small + i;
    for (unsigned i = 0; i < ARRAY_SIZE(array_indirect_skip); ++i)
        array_indirect_skip[i] = array + 2 * i;

    test_equals_int(averageIndirect(array_indirect, ARRAY_SIZE(array_indirect)), 55,
        "indirect average of array should be 55");
    test_equals_int(averageIndirect(small_indirect, 1), 1,
        "indirect average of single element should be element");
    test_equals_int(averageIndirect(small_indirect, ARRAY_SIZE(small_indirect)), 1,
        "indirect average should round down");
    test_equals_int(averageIndirect(array_indirect_skip, ARRAY_SIZE(array_indirect_skip)), 30,
        "you actually dereference the correct indirect pointers");

    return 0;
}
