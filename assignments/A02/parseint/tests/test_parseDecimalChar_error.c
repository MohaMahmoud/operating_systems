#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseDecimalChar returns -1 for non-digits.");

    test_equals_int(parseDecimalChar('x'), -1, "x");
    test_equals_int(parseDecimalChar('?'), -1, "?");
    test_equals_int(parseDecimalChar('9' + 1), -1, "'9' + 1");
    test_equals_int(parseDecimalChar('a'), -1, "a");

    return test_end();
}
