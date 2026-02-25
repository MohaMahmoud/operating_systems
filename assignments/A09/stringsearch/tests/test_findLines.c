#include "testlib.h"
#include "stringsearch.h"
#include <string.h>
#include <stdlib.h>

int main() {
    test_start("Your findLines works for our test cases.");

    test_plan(8);

    char *haystack = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam";
    Lines *lines;

    lines = findLines(haystack, strlen(haystack));
    test_equals_int(lines->len, 0, "works for a sentece without new line");
    free(lines);


    haystack = "first\n\nsecond\n";
    lines = findLines(haystack, strlen(haystack));
    test_equals_int(lines->len, 3, "works for a sentece with an empty line");
    test_equals_int(lines->lines[0].len, 6, "first line is 'first' with length (including new line) 6");
    test_equals_int(*lines->lines[0].start, 'f', "first line starts with char 'f'");
    test_equals_int(lines->lines[1].len, 1, "second line is empty");
    test_equals_int(*lines->lines[1].start, '\n', "is empty");
    test_equals_int(lines->lines[2].len, 7, "third line is 'second' with length (including new line) 7");
    test_equals_int(*lines->lines[2].start, 's', "third line starts with char 's'");

    free(lines);
    return test_end();
}