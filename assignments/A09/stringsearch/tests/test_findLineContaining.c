#include "testlib.h"
#include "stringsearch.h"
#include <string.h>
#include <stdlib.h>

int main() {
    test_start("Your findLineContaining works for our test cases.");

    test_plan(3);

    char *haystack = "Lorem ipsum dolor sit amet,\n consetetur sadipscing elitr,\n sed diam\n";
    Lines *lines;
    Line *result;

    lines = findLines(haystack, strlen(haystack));
    result = findLineContaining(lines, &haystack[0]);
    test_equals_ptr(result, &lines->lines[0], "findLineContaining finds first line");

    result = findLineContaining(lines, &haystack[40]);
    test_equals_ptr(result, &lines->lines[1], "findLineContaining finds second line");

    result = findLineContaining(lines, &haystack[67]);
    test_equals_ptr(result, &lines->lines[2], "findLineContaining finds last line");
    free(lines);

    return test_end();
}