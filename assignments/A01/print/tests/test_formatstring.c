#include "testlib.h"
#include "print.h"
#include <stdio.h>
#include <stdarg.h>

static int check = 0;

int __wrap_printf(const char *format, ...) {
    if (check) {
        check = 0;
        test_equals_string(format, "%" PRId64 " %s\n", "format string is correct");
    }
    va_list argptr;
    va_start(argptr, format);
    int res = vprintf(format, argptr);
    va_end(argptr);
    return res;
}

int main() {
    test_start("You pass the right format string to printf.");
    test_plan(1);
    check = 1;
    print_line(43, "abcdef");
    check = 0;
    return test_end();
}
