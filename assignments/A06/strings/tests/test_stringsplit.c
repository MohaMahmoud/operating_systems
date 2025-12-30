#include "testlib.h"
#include "strings.h"

#include <sanitizer/lsan_interface.h>

int isTheSameWhenAddingDelimiterBack(char **substrings, char delimiter, char *originalString)
{
    char *currentSubstring;
    while(*substrings != NULL) {
        currentSubstring = *substrings;
        while (*currentSubstring) {
            if(*currentSubstring != *originalString) {
                return 0;
            }
            ++originalString;
            ++currentSubstring;
        }
        
        
        ++substrings;
        if(*originalString != delimiter && *substrings != NULL) {
            return 0;
        }
        ++originalString;
    }
    if(*(--originalString) != '\0') {
        return 0;
    }
    return 1;
}

int lengthOfResult(char **result)
{
    int length = 0;
    while (*result++ != NULL) {
        ++length;
    }
    return length;
}

int main()
{
    test_start("Your stringsplit works for our test cases.");

    test_plan(27);

    char **result;
    result = stringsplit("one|two|three", '|');
    test_equals_int(lengthOfResult(result), 3, "stringsplit for 'one|two|three' with delimiter '|' returns correct number of substrings");
    test_equals_string(result[0], "one", "stringsplit for 'one|two|three' with delimiter '|' returns 'one' as first substring");
    test_equals_string(result[1], "two", "stringsplit for 'one|two|three' with delimiter '|' returns 'two' as second substring");
    test_equals_string(result[2], "three", "stringsplit for 'one|two|three' with delimiter '|' returns 'three' as third substring");
    test_equals_ptr(result[3], NULL, "stringsplit for for 'one|two|three' with delimiter '|' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);

    result = stringsplit(",,,", ',');
    test_equals_int(lengthOfResult(result), 4, "stringsplit for ',,,' with delimiter ',' returns correct number of substrings");
    test_equals_string(result[0], "", "stringsplit for ',,,' with delimiter ',' returns '' as first substring");
    test_equals_string(result[1], "", "stringsplit for ',,,' with delimiter ',' returns '' as second substring");
    test_equals_string(result[2], "", "stringsplit for ',,,' with delimiter ',' returns '' as third substring");
    test_equals_string(result[3], "", "stringsplit for ',,,' with delimiter ',' returns '' as fourth substring");
    test_equals_ptr(result[4], NULL, "stringsplit for for ',,,' with delimiter ',' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);

    result = stringsplit("AHA", 'A');
    test_equals_int(lengthOfResult(result), 3, "stringsplit for 'AHA' with delimiter 'A' returns correct number of substrings");
    test_equals_string(result[0], "", "stringsplit for 'AHA' with delimiter 'A' returns '' as first substring");
    test_equals_string(result[1], "H", "stringsplit for 'AHA' with delimiter 'A' returns 'H' as second substring");
    test_equals_string(result[2], "", "stringsplit for 'AHA' with delimiter 'A' returns '' as third substring");
    test_equals_ptr(result[3], NULL, "stringsplit for for 'AHA' with delimiter 'A' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);

    result = stringsplit("happy day", '.');
    test_equals_int(lengthOfResult(result), 1, "stringsplit for 'happy day' with delimiter '.' returns correct number of substrings");
    test_equals_string(result[0], "happy day", "stringsplit for 'happy day' with delimiter '.' returns 'happy day' as first substring");
    test_equals_ptr(result[1], NULL, "stringsplit for for 'happy day' with delimiter '.' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);

    result = stringsplit("", '!');
    test_equals_int(lengthOfResult(result), 1, "stringsplit for empty string with delimiter '!' returns correct number of substrings");
    test_equals_string(result[0], "", "stringsplit for empty string with delimiter '!' returns empty string as first substring");
    test_equals_ptr(result[1], NULL, "stringsplit for for empty string with delimiter '!' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);

    result = stringsplit("Exuberance", 'B');
    test_equals_int(lengthOfResult(result), 1, "stringsplit for 'Exuberance' with delimiter 'B' returns correct number of substrings");
    test_equals_string(result[0], "Exuberance", "stringsplit is case sensitive");
    test_equals_ptr(result[1], NULL, "stringsplit for for 'Exuberance' with delimiter 'B' returns result that is correctly terminated by NULL pointer");
    stringsplit_free(result);


    char *loremipsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
    result = stringsplit(loremipsum, ' ');
    test_equals_int(isTheSameWhenAddingDelimiterBack(result, ' ', loremipsum), 1, "stringsplit for lorem ipsum seperating 100 words and putting them back together works");
    stringsplit_free(result);

    test_assert(!__lsan_do_recoverable_leak_check(), "there are no memory leaks");

    return test_end();
}
