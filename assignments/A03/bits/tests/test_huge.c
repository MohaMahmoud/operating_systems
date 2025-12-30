#include "testlib.h"
#include "bits.h"

#include <sys/mman.h>
#include <linux/mman.h>

int main()
{
    test_start("Your getN/setN/clrN functions work with a huge array.");
    test_plan(6);

    // idx is large enough so that trying to use `(unsigned) int` instead of `size_t` fails.
    size_t idx = 1ULL << 38;

    // Allocate non-accessible virtual memory (always cheap!).
    uint64_t *mem = mmap(NULL, idx / 8 + 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    test_assert(mem != MAP_FAILED, "mmap");
    // Make the last page readable and writable for the following assertions.
    test_assert(mprotect(&mem[idx / 64], 4096, PROT_READ | PROT_WRITE) == 0, "mprotect");

    setN(mem, idx);
    test_equals_int64(mem[idx / 64], 0x1, "setting 2^38'th bit");
    test_equals_int(getN(mem, idx), 1, "getting 2^38'th bit");

    clrN(mem, idx);
    test_equals_int64(mem[idx / 64], 0, "clearing 2^38'th bit");
    test_equals_int(getN(mem, idx), 0, "getting 2^38'th bit");

    return test_end();
}
