#include "testlib.h"
#include "binarysearch.h"

int main()
{
    test_start("binary-search.c");
    const char* someStrings[3] = {"OS", "is", "super"};

    test_equals_int(binarySearch("super", someStrings,  3), 2, "You find super at correct index of the array.");
    test_equals_int(binarySearch("cvid", someStrings,  3), -1, "Your binary search determines correctly that cvid is not a word in the array.");


    return 0;
}
