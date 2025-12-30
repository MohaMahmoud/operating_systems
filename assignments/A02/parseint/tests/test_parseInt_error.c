#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseInt returns -1 for non-digits");

    test_equals_int(parseInt("0x0"), -1, "0x0");
    test_equals_int(parseInt("a"), -1, "a");
    test_equals_int(parseInt(""), -1, "(empty string)");
    test_equals_int(parseInt("100a"), -1, "100a");
    test_equals_int(parseInt("010?"), -1, "010?");

    return test_end();
}
