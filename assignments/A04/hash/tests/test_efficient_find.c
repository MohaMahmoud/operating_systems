#include "testlib.h"
#include "hash.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your find function does not do unnecessary array lookups.");
    test_plan(2);

    // We construct an invalid hash table filled with entries for "A".
    element e[5] = {
        {.valid = 1, .key = "A", .value = -1},
        {.valid = 1, .key = "A", .value = -1},
        {.valid = 1, .key = "A", .value = -1},
        {.valid = 1, .key = "A", .value = 42},
        {.valid = 1, .key = "A", .value = -1}
    };
    hashtable h = {e, sizeof(e)/sizeof(e[0])};

    int val = 0;
    test_equals_int(find(&h, "A", &val), 1, "retrieving A succeeds");
    test_equals_int(val, 42, "find got the correct value");

    return test_end();
}

