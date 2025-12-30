#include "testlib.h"
#include "pointers.h"

#include "stddef.h"

#define ARRAY_SIZE(element) (sizeof(element) / sizeof(*(element)))

int main()
{
    test_start("Your averages handle negative numbers correctly.");
    test_plan(4);

    int small[] = {-1, -2, -4, -6};

    int *small_indirect[ARRAY_SIZE(small)] = {0};
    for (unsigned i = 0; i < ARRAY_SIZE(small); ++i)
        small_indirect[i] = small + i;

    test_equals_int(average(small + 2, 2), -5,
        "average of negative numbers work");
    test_equals_int(averageIndirect(small_indirect + 2, 2), -5,
        "indirect average of negative numbers work");

    test_equals_int(average(small, 2), -1,
        "rounding of negative numbers work");
    test_equals_int(averageIndirect(small_indirect, 2), -1,
        "indirect rounding of negative numbers work");

    return 0;
}
