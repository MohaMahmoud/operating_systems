#include "testlib.h"
#include "pointers.h"

#include "stddef.h"

int main()
{
    test_start("Your averages handle empty arrays correctly.");
    test_plan(2);

    test_equals_int(average(NULL, 0), 0,
        "average of empty array should be 0");
    test_equals_int(averageIndirect(NULL, 0), 0,
        "indirect average of empty array should be 0");

    return 0;
}
