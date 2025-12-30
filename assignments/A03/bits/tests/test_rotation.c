#include "testlib.h"
#include "bits.h"

int main()
{
    test_start("Your rot function works.");
    test_plan(6);

	uint64_t d1 = 0x0000111122223333;
	uint64_t d2 = 0x3333000011112222;

    test_equals_int64(rot(d1, 0), d1, "rotation by 0 does not modify");
    test_equals_int64(rot(d1, +16), d2, "rotation by +16");
    test_equals_int64(rot(d2, -16), d1, "rotation by -16");
    test_equals_int64(rot(d2, -16-64), d1, "rotation by -16-64 (round trip)");
    test_equals_int64(rot(d1, +64), d1, "rotation by +64 (round trip)");
    test_equals_int64(rot(d2, -128), d2, "rotation by -128 (round trip)");

    return test_end();
}

