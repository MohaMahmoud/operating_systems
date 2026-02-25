#include "testlib.h"
#include "memset.h"


int main() {
    test_start("You rotate our test cases correctly");
    test_plan(4);

    uint64_t zero = 0x0ull;
    test_equals_int64(rotr(zero), 0x0ull, "Rotates 0x0 correctly");

    uint64_t test = 0xABCDEF0123456789ull;
    test = rotr(test);
    test_equals_int64(test, 0x89ABCDEF01234567ull, "Rotating once works.");
    for (size_t i = 0; i < 7; i++) {
        test = rotr(test);
    }
    test_equals_int64(test, 0xABCDEF0123456789ull, "Rotating 8 times result in the integer we started rotating with");

    test = 0x0000000110000000ull;
    test_equals_int64(rotr(test), 0x0000000001100000ull, "Rotating once works for 0000000110000000");

     
    
    return test_end();
}
