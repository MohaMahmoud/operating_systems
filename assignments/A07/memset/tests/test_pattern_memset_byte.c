#include "testlib.h"
#include "memset.h"


int main() {
    test_start("You write, with pattern_memset_byte, our test patterns correctly to the buffer");
    test_plan(9);

    uint64_t pat = 0x123456789ABCDEF0ull;
    char buf[5];
    pattern_memset_byte(buf, &pat, 5);
    test_equals_int64(pat,  0x789ABCDEF0123456ull, "calling pattern_memset_byte results in the pattern being rotated correctly");
    test_equals_int((unsigned int) buf[0], 0xfffffff0 , "calling pattern_memset_byte with basic pattern writes the first byte correctly to the buffer: buffer[0] = F0");
    test_equals_int((unsigned int) buf[1], 0xffffffde , "calling pattern_memset_byte with basic pattern writes the second byte correctly to the buffer: buffer[1] = DE");
    test_equals_int((unsigned int) buf[2], 0xffffffbc , "calling pattern_memset_byte with basic pattern writes the third byte correctly to the buffer: buffer[2] = BC");
    test_equals_int((unsigned int) buf[3], 0xffffff9A , "calling pattern_memset_byte with basic pattern writes the fourth byte correctly to the buffer: buffer[3] = 9A");
    test_equals_int((unsigned int) buf[4], 0x78 , "calling pattern_memset_byte with basic pattern writes the fifth byte correctly to the buffer: buffer[4] = 78");


    pat = 0x123456789ABCDEF0ull;
    char biggerBuffer[9];
    pattern_memset_byte(biggerBuffer, &pat, 9);
    test_equals_int64(pat,  0xF0123456789ABCDEull, "calling pattern_memset_byte with bigger buffer to break usage of memcpy, results in the pattern being rotated correctly");
    test_equals_int((unsigned int) biggerBuffer[8], 0xfffffff0 , "calling pattern_memset_byte with bigger buffer writes 9th byte correctly to the buffer: buffer[8] = F0");
    test_equals_int((unsigned int) biggerBuffer[8], (unsigned int) biggerBuffer[0] , "this buffer size needs rotating entirely which is why the first buffer element should be the same as the last.");

    
    return test_end();
}