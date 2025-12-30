#include "testlib.h"
#include "parseint.h"

int main() {
    test_start("parseInt returns -1 for illegal octal numbers");

    test_equals_int(parseInt("08"), -1, "08");
    test_equals_int(parseInt("03729"), -1, "03729");

    return test_end();
}
