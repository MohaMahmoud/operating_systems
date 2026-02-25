#include "testlib.h"
#include "stringsearch.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
pthread_cond_t _cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
bool _linesValid = false;
Lines *_lines = NULL;
char *_haystack = "How much wood would a woodchuck chuck\nif a woodchuck could chuck wood?\nHe would chuck, he would, as much as he could,\nand chuck as much wood as a woodchuck would\nif a woodchuck could chuck wood.\n";



int __wrap_pthread_cond_wait(pthread_cond_t *restrict cond,
                             pthread_mutex_t *restrict mutex) {
    test_equals_ptr(cond, &_cond, "you call pthread_cond_wait with correct condition");
    test_equals_ptr(mutex, &_mutex, "you call pthread_cond_wait with correct mutex");
    if(!_linesValid) {
        _lines = findLines(_haystack, strlen(_haystack));
        _linesValid = true;
    }
    return 0;
}

int main() {
    test_start("Your needleSearcher waits until the lines are ready.");

    test_plan(7);

   

    NeedleSearcherState searchState = {.needle = "woodchuck", .haystack = _haystack, .len = strlen(_haystack), .cond = &_cond, .mutex = &_mutex, .lines_valid = &_linesValid, .lines = &_lines};
    pthread_t needleSearcherThread;
    pthread_create(&needleSearcherThread, NULL, needleSearcher, &searchState);

    NeedleSearcherResult *result;
    pthread_join(needleSearcherThread, (void **) &result);
    test_equals_ptr(result->line->start, &_haystack[0], "needle search in woodchuck tongue twister for 'woodchuck' contains first line as correct result");
    NeedleSearcherResult *nextResult = result->next;
    free(result);
    result = nextResult;
    test_equals_ptr(result->line->start, &_haystack[38], "needle search in woodchuck tongue twister for 'woodchuck' contains second line as correct result");
    nextResult = result->next;
    free(result);
    result = nextResult;
    test_equals_ptr(result->line->start, &_haystack[118], "needle search in woodchuck tongue twister for 'woodchuck' contains fourth line as correct result");
    nextResult = result->next;
    free(result);
    result = nextResult;
    test_equals_ptr(result->line->start, &_haystack[162], "needle search in woodchuck tongue twister for 'woodchuck' contains fifth line as correct result");
    nextResult = result->next;
    free(result);

    test_equals_ptr(nextResult, NULL, "needle search in woodchuck tongue twister for 'woodchuck' correctly no more results");

    free(_lines);

    return test_end();
}