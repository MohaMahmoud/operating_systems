#include "testlib.h"
#include "hash.h"

int main()
{
    test_start("Your hashString function works.");
    test_plan(3);

    test_equals_int64(hashString(""), 5381, "(empty string)");
    test_equals_int64(hashString("A"), 177638, "A");
    test_equals_int64(hashString("Hello world!"), 13594750394883323106ULL, "Hello world!");

    return test_end();
}

