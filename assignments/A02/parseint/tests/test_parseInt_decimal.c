#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseInt can parse decimal numbers.");

    test_equals_int(parseInt("1"), 1, "1");
    test_equals_int(parseInt("10"), 10, "10");
    test_equals_int(parseInt("139483"), 139483, "139483");
    test_equals_int(parseInt("39387283"), 39387283, "39387283");

    return test_end();
}
