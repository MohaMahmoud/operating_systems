#include "testlib.h"
#include "binarysearch.h"

int main() {
    test_start("you compare strings correctly.");
    test_plan(5);

    char different_address[] = {0};
    test_equals_int(compareStrings("foobar", "foobar"), 0, "two equal strings are equal");
    test_equals_int(compareStrings("", different_address), 0, "empty strings are equal");
    test_assert(compareStrings("foobar", "baz") != 0, "different strings are different");
    test_assert(compareStrings("ZZZZZZZZ", "AAAAAAA") > 0, "lexicographic sort is correct");
    test_assert(compareStrings("foobar", "foo") > 0, "substrings are smaller than the string itself");

    return test_end();
}

