#include "testlib.h"
#include "hash.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    test_start("Your insert and find functions work for basic operations.");
    test_plan(13);

    element e[10] = {{0}};
    hashtable h = {e, sizeof(e)/sizeof(e[0])};

    /*
    char *strings[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", NULL};
    for (char **s = strings; *s; s++) {
        printf("h(%s) = %d\n", *s, (int) (hashString(*s) % 10));
    }
    */

    test_equals_int(insert(&h, "A", 42), 1, "inserting A succeeds");
    test_equals_int(e[8].value, 42, "A was inserted into the correct slot");
    test_equals_int(insert(&h, "D", 84), 1, "inserting D succeeds");
    test_equals_int(e[1].value, 84, "D's value was inserted into the correct slot");
    test_equals_int(e[1].valid != 0, 1, "D is marked as valid");

    int val = 0;
    test_equals_int(find(&h, "D", &val), 1, "retrieving D succeeds");
    test_equals_int(val, 84, "find got the correct value");
    test_equals_int(find(&h, "B", &val), 0, "retrieving B fails");
    // K has same slot as A
    test_equals_int(find(&h, "K", &val), 0, "retrieving K fails");

    char a[] = "A";
    assert(a != e[8].key && "stack copy has a different pointer value");
    // would fail when not using strcmp() or a similar function
    test_equals_int(find(&h, a, &val), 1, "retrieving A succeeds with different string pointer");
    test_equals_int(val, 42, "find got the correct value");

    test_equals_int(insert(&h, "A", 99), 1, "overwriting A succeeds");
    test_equals_int(e[8].value, 99, "A's value was correctly overwritten");

    return test_end();
}


