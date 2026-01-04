#include <stdint.h>

#include "bits.h"

/*
 * Returns the n'th bit of the array A.
 */
int getN(uint64_t *A, size_t n)
{
    (void) A;
    (void) n;

    return (A[n/64] >> (n % 64)) & 1;
}

/*
 * Sets the n'th bit of the array A.
 */
void setN(uint64_t *A, size_t n)
{
    (void) A;
    (void) n;
    uint64_t mask = 1ULL << (n % 64); // Create a mask with a 1 at the n'th position
    A[n/64] = A[n/64] | mask;
}

/*
 * Clears the n'th bit of the array A.
 */
void clrN(uint64_t *A, size_t n)
{
    (void) A;
    (void) n;
    uint64_t mask = ~(1ULL << (n % 64)); // Create a mask with a 0 at the n'th position
    A[n/64] = A[n/64] & mask;
}


/*
 * Rotates the integer i n bits to the right.
 */
uint64_t rot(uint64_t i, int n)
{
    (void) i;
    (void) n;
    n = n % 64; // Ensure n is within the range of 0-63
    return (i >> n) | (i << (64 - n)); 
}
