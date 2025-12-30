#define _GNU_SOURCE
#include "testlib.h"
#include "print.h"
#include <stdio.h>
#include <string.h>

int main()
{
    test_start("Your print_line prints the line properly.");
    test_plan(2);

    char buf[100];
    FILE *fmem = fmemopen(buf, sizeof(buf), "w");
    FILE *real_stdout = stdout;

#define WITH_FMEM(code) stdout = fmem; code; fflush(fmem); stdout = real_stdout;

    WITH_FMEM(print_line(1234567890, "hello world"));
    test_equals_string(buf, "1234567890 hello world\n", "print_line prints: 1234567890 hello world");
    rewind(fmem);

    WITH_FMEM(print_line((uint64_t)1<<63, "negative number"));
    test_equals_string(buf, "-9223372036854775808 negative number\n", "print_line prints: -9223372036854775808 negative number");
    rewind(fmem);

    fclose(fmem);
    return test_end();
}
