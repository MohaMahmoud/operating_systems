#include "testlib.h"
#include "bits.h"

static int popcnt(uint64_t *A, int max)
{
    int c = 0;
    for (int i = 0; i < max; i++) {
        c += getN(A, i);
    }
    return c;
}

int main()
{
    test_start("Your getN/setN/clrN functions work with a single integer.");
    test_plan(10);

    uint64_t x = 0;

    setN(&x, 0);
    test_equals_int64(x, 0x1, "setting 0'th bit");
    test_equals_int(getN(&x, 0), 1, "getting 0'th bit");

    setN(&x, 0);
    test_equals_int64(x, 0x1, "setting 0'th bit twice"); // no toggle!

    setN(&x, 15);
    test_equals_int64(x, 0x8001, "setting 15'th bit");
    setN(&x, 63);
    test_equals_int64(x, 0x8000000000008001, "setting 63'rd bit");
    test_equals_int(getN(&x, 63), 1, "getting 63'rd bit");
    test_equals_int(getN(&x, 62), 0, "getting 62'nd bit");
    test_equals_int(popcnt(&x, 64), 3, "population count");

    clrN(&x, 0);
    clrN(&x, 0); // no toggle!
    clrN(&x, 63);
    test_equals_int64(x, 0x8000, "clearing 0'th and 63'rd bits");

    uint64_t y = 0x1234567890ABCDEF;
    test_equals_int(popcnt(&y, 64), 32, "population count of 0x1234567890ABCDEF");

    return test_end();
}
