#include "memset.h"
/**
 * Rotates a 64 bit integer by one byte (8 bit) to the right.
 */
uint64_t rotr(uint64_t v) {
    return (v >> 8) | (v << 56);
}

/**
 * Writes the pattern in *pat byte-by-byte to the memory area pointed to with s and of length n.
 * After the call the pattern in *pat should be rotated so that the next byte to write is at the front of the pattern.
 * As a result calling pattern_memset_byte again with the same pattern will continue the pattern.
 */
void pattern_memset_byte(void *s, uint64_t *pat, size_t n) {
    unsigned char *buf = (unsigned char *)s;
    for (size_t i = 0; i<n; i++) {
        buf[i] = (unsigned char)(*pat & 0xFF);
        *pat = rotr(*pat);
    }
}

/**
 * Writes the pattern pat to the memory area starting at s of length n.
 * The function should minimize the number of memory accesses.
 */
void pattern_memset(void *s, uint64_t pat, size_t n) {
    
    uint64_t current_pat = pat;
    unsigned char *addr = (unsigned char *)s;

    while ( ((uintptr_t)addr & 0x7 != 0) && (n > 0) ) {
        pattern_memset_byte(addr, &current_pat, 1);
        addr += 1;
        n    -= 1;
    }
    
    while (n >= 8) {
        *(uint64_t *)addr = current_pat;
        
        addr += 8;
        n    -= 8;
    }

    
    if (n > 0) {
        pattern_memset_byte(addr, &current_pat, n);
    }
}
