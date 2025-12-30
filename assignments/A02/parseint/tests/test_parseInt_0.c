#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseInt can handle 0");

    test_equals_int(parseInt("0"), 0, "0");
    test_equals_int(parseInt("00"), 0, "00");

    return test_end();
}
