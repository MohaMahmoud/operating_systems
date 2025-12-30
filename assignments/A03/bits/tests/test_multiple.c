#include "testlib.h"
#include "bits.h"

#include <string.h>
#include <sys/mman.h>
#include <linux/mman.h>

static int popcnt(uint64_t *A, int max)
{
    int c = 0;
    for (int i = 0; i < max; i++) {
        c += getN(A, i);
    }
    return c;
}

int main()
{
    test_start("Your getN/setN/clrN functions work with an array of integers.");
    test_plan(7);

    // Allocate three pages of non-accessible virtual memory.
    char *mem = mmap(NULL, 3 * 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    test_assert(mem != MAP_FAILED, "mmap");
    // Make the middle page accessible.
    test_assert(mprotect(&mem[4096], 4096, PROT_READ | PROT_WRITE) == 0, "mprotect");

    size_t size = 21;
    // Place A at the end of the accessible page.
    uint64_t *A = (uint64_t *) &mem[2*4096 - 8*size];

    for (size_t i = 0; i < 64*size; i += 3) {
        setN(A, i);
    }
    int ok = 1;
    for (size_t i = 0; i < size; i += 3) {
        ok &= A[i]   == 0x9249249249249249;
        ok &= A[i+1] == 0x4924924924924924;
        ok &= A[i+2] == 0x2492492492492492;
    }
    test_assert(ok, "setting every third bit");
    test_equals_int(popcnt(A, 64*size), 64*size/3, "population count with every third bit set");

    memset(A, 0xFF, 8*size);
    test_equals_int(popcnt(A, 64*size), 64*size, "population count with every bit set");

    for (size_t i = 0; i < 64*size; i += 3) {
        clrN(A, i);
    }
    ok = 1;
    for (size_t i = 0; i < size; i += 3) {
        ok &= A[i]   == 0x6DB6DB6DB6DB6DB6;
        ok &= A[i+1] == 0xB6DB6DB6DB6DB6DB;
        ok &= A[i+2] == 0xDB6DB6DB6DB6DB6D;
    }
    test_assert(ok, "clearing every third bit");
    test_equals_int(popcnt(A, 64*size), 64*size*2/3, "population count with every third bit cleared");

    return test_end();
}

