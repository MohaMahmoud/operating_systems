#include "testlib.h"
#include "stringsearch.h"

int main() {
    test_start("Your findFirstSubstring works for our test cases.");

    test_plan(5);

    char *needle = "find";
    char *haystack = "some text";
    test_equals_int(findFirstSubstring(needle, haystack, 2), -1, "a needle that is longer than the number of bytes to search can not be found");

    needle = "find";
    haystack = "some text";
    test_equals_int(findFirstSubstring(needle, haystack, 9), -1, "some text' does not contain 'find'");

    needle = "find";
    haystack = "fin some text";
    test_equals_int(findFirstSubstring(needle, haystack, 13), -1, "fin some text' does not contain 'find'");


    needle = "find";
    haystack = "fin some text find";
    test_equals_int(findFirstSubstring(needle, haystack, 18), 14, "fin some text find' does contain 'find' at offset 14");

    needle = "hello";
    haystack = "helloworld";
    test_equals_int(findFirstSubstring(needle, haystack, 10), 0, "helloworld' does contain 'hello' at offset 0");

    return test_end();
}