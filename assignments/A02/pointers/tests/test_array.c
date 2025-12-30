#include "testlib.h"
#include "pointers.h"

#include "stddef.h"

#define ARRAY_SIZE(element) (sizeof(element) / sizeof(*(element)))

int main()
{
    test_start("You calculate correct averages without indirection.");
    test_plan(3);

    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int small[] = {1, 2};

    test_equals_int(average(array, ARRAY_SIZE(array)), 55,
        "average of array should be 55");
    test_equals_int(average(small, 1), 1,
        "average of single element should be element");
    test_equals_int(average(small, ARRAY_SIZE(small)), 1,
        "average should round down");

    return 0;
}
