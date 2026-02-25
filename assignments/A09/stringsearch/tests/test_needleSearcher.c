#include "testlib.h"
#include "stringsearch.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


int main() {
    test_start("Your needleSearcher works for our test cases.");

    test_plan(5);
     char *haystack = "Lorem ipsum dolor sit amet,\n consetetur sadipscing elitr,\n sed diam\n";
 
    Lines *lines;
    lines = findLines(haystack, strlen(haystack));
    bool linesValid = true;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    NeedleSearcherState searchState = {.needle = "Lorem ipsum", .haystack = haystack, .len = strlen(haystack), .cond = &cond, .mutex = &mutex, .lines_valid = &linesValid, .lines = &lines};
    NeedleSearcherResult *result = (NeedleSearcherResult*) needleSearcher((void*)&searchState);
    test_equals_ptr(result->next, NULL, "needle search in Lorem ipsum for 'Lorem ipsum' contains only one result");
    test_equals_ptr(result->line->start, &haystack[0], "needle search in Lorem ipsum for 'Lorem ipsum' returns first line as correct result");
    free(result);
    free(lines);


    searchState.needle = "hello";
    result = (NeedleSearcherResult*) needleSearcher((void*)&searchState);
    test_equals_ptr(result, NULL, "needle search in Lorem ipsum for 'hello' correctly returns empty result");
   
    haystack = "hannahannah\n";
    lines = findLines(haystack, strlen(haystack));
    searchState.haystack = haystack;
    searchState.len = strlen(haystack);
    searchState.needle = "hannah";
    result = (NeedleSearcherResult*) needleSearcher((void*)&searchState);
    test_equals_ptr(result->next, NULL, "no overlap: needle search in 'hannahannah' for 'hannah' contains only one result");
    test_equals_ptr(result->line->start, &haystack[0], "no overlap: needle search in 'hannahannah' for 'hannah' contains first line as correct result");
    free(result);
    free(lines);


    return test_end();
}