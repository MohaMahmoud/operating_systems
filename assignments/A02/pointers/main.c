#include "testlib.h"
#include "pointers.h"

int main()
{
    test_start("pointers.c");
    test_plan(2);

    // arrays of six elements
    // (consider what each position contains...)
    int array[6] = {1, 2, 3, 4, 5};

    // create array of pointers to int
    int *(pointers[6]) = {0};
    // and initialize each element to point
    // to the respective element in array
    for (int i = 0; i < 6; ++i)
        pointers[i] = &(array[i]);

    // execute the actual tests
    test_equals_int(average(array, 6), 2, "averaging works");
    test_equals_int(averageIndirect(pointers, 6), 2, "indirect averaging works");

    return test_end();
}
