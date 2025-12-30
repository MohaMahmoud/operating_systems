#include "testlib.h"
#include "strings.h"
#include <stdio.h>

/*
size_t __wrap_strlen(const char *s) {
	test_failed_message("String library functions are not allowed");
	return 0;
}
*/
int main()
{
    test_start("Your stringlength works for our test cases.");

    test_plan(4);

    test_equals_int(stringlength("\0"), 0, "stringlength works for empty string");
    test_equals_int(stringlength("Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea"), 246, "stringlength works for 246 long string");
    test_equals_int(stringlength("h3ll0 w0rld"), 11, "stringlength works for 'h3ll0 w0rld'");
    test_equals_int(stringlength("a"), 1, "stringlength works for 'a'");


    
    return test_end();
}