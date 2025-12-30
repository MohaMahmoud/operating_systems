#include "testlib.h"
#include "hash.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your implemented linear probing correctly.");
    test_plan(11);

    element e[10] = {{0}};
    hashtable h = {e, sizeof(e)/sizeof(e[0])};

    /* for (unsigned char c = 'A'; c < 128; c += 10) printf("%c\n", c); */

    test_equals_int(insert(&h, "A", 42), 1, "inserting A succeeds");
    test_equals_int(insert(&h, "K", 43), 1, "inserting K succeeds");
    test_equals_int(insert(&h, "U", 44), 1, "inserting U succeeds");
    test_equals_int(insert(&h, "B", 84), 1, "inserting B succeeds");
    test_equals_int(e[9].value, 43, "K was inserted into the correct slot");
    test_equals_int(e[0].value, 44, "U was inserted into the correct slot");
    test_equals_int(e[1].value, 84, "B was inserted into the correct slot");

    int val = 0;
    test_equals_int(find(&h, "U", &val), 1, "retrieving U succeeds");
    test_equals_int(val, 44, "find got the correct value");
    test_equals_int(find(&h, "B", &val), 1, "retrieving B succeeds");
    test_equals_int(val, 84, "find got the correct value");

    return test_end();
}
