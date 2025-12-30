#include "testlib.h"
#include "hash.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your insert and find functions work correctly when the hash table is full.");
    test_plan(11);

    element e[5] = {{0}};
    hashtable h = {e, sizeof(e)/sizeof(e[0])};

    test_equals_int(insert(&h, "A", 42), 1, "inserting A succeeds");
    test_equals_int(insert(&h, "F", 43), 1, "inserting F succeeds");
    test_equals_int(insert(&h, "K", 44), 1, "inserting K succeeds");
    test_equals_int(insert(&h, "B", 45), 1, "inserting B succeeds");
    test_equals_int(insert(&h, "C", 46), 1, "inserting C succeeds");

    test_equals_int(insert(&h, "D", 47), 0, "inserting D fails");
    test_equals_int(insert(&h, "K", 99), 1, "overwriting K succeeds");
    test_equals_int(e[0].value, 99, "K has correct value");

    int val = 0;
    test_equals_int(find(&h, "B", &val), 1, "retrieving B succeeds");
    test_equals_int(val, 45, "find got the correct value");
    test_equals_int(find(&h, "X", &val), 0, "retrieving X fails");

    return test_end();
}
