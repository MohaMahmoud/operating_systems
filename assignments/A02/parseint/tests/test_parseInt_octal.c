#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseInt can parse octal numbers.");

    test_equals_int(parseInt("01"), 01, "01");
    test_equals_int(parseInt("010"), 010, "010");
    test_equals_int(parseInt("032372"), 032372, "032372");
    test_equals_int(parseInt("0672101"), 0672101, "0672101");

    return test_end();
}
