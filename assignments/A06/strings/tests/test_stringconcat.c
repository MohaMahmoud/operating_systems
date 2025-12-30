#include "testlib.h"
#include "strings.h"

int main()
{
    test_start("Your stringconcat works for our test cases.");

    test_plan(4);

    char *result;
    result = stringconcat("OS is", " fun");
    test_equals_string(result, "OS is fun", "stringconcat correctly concatenates 'OS is' with ' fun'");
    free(result);
    result = stringconcat("", "");
    test_equals_string(result, "", "stringconcat correctly concatenates two empty strings");
    free(result);
    result = stringconcat("\0", "Right");
    test_equals_string(result, "Right", "stringconcat correctly concatenates null byte with 'Right'");
    free(result);
    result = stringconcat("O", "S");
    test_equals_string(result, "OS", "stringconcat correctly concatenates 'O' with 'S'");
    free(result);

    return test_end();
}