#define _GNU_SOURCE
#include "testlib.h"
#include "parseint.h"
#include <stdlib.h>
#include <string.h>

int main() {
    test_start("parseDecimalChar converts all digits.");
    test_plan(10);

    char *desc = strdup("parseDecimalChar converts 0");
    char *digit = desc + 26;
    char i = 0;
    for (i = 0; i < 10; i++) {
        *digit = '0' + i;
        test_equals_int(parseDecimalChar(*digit), i, desc);
    }
    free(desc);

    return test_end();
}
