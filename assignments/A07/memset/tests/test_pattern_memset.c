#include "testlib.h"
#include "memset.h"
#include <stdio.h>


int main() {
    test_start("You write, with pattern_memset, our test patterns correctly to the buffer");
    test_plan(72);

    uint64_t pat = 0x123456789ABCDEF0ull;
    unsigned char buf[5];
    pattern_memset(buf, pat, sizeof(buf));
    test_equals_int(buf[0], 0xf0 , "calling pattern_memset with pattern that is larger than the buffer writes the first byte correctly to the buffer: buffer[0] = F0");
    test_equals_int(buf[1], 0xde , "calling pattern_memset with pattern that is larger than the buffer writes the second byte correctly to the buffer: buffer[1] = DE");
    test_equals_int(buf[2], 0xbc , "calling pattern_memset with pattern that is larger than the buffer writes the third byte correctly to the buffer: buffer[2] = BC");
    test_equals_int(buf[3], 0x9a , "calling pattern_memset with pattern that is larger than the buffer writes the fourth byte correctly to the buffer: buffer[3]] = 9A");
    test_equals_int(buf[4], 0x78 , "calling pattern_memset with pattern that is larger than the buffer writes the fifth byte correctly to the buffer: buffer[4] = 78");


    pat = 0x0000000000000000ull;
    unsigned char bufOne;
    pattern_memset(&bufOne, pat, sizeof(bufOne));
    test_equals_int(bufOne, 0x00 , "calling pattern_memset with zero pattern and bufer of size one writes the byte correctly to the buffer: buffer[0] = 00");
    
    pat =  0x0011223344556677ull;
    
    unsigned char bufPerfectFit[sizeof(pat)];
    pattern_memset(bufPerfectFit, pat, sizeof(bufPerfectFit));
    test_equals_int(bufPerfectFit[0], 0x77 , "calling pattern_memset with pattern that fits buffer perfectly writes the 1st byte correctly to the buffer: buffer[0] = 77");
    test_equals_int(bufPerfectFit[1], 0x66 , "calling pattern_memset with pattern that fits buffer perfectly writes the 2nd byte correctly to the buffer: buffer[1] = 66");
    test_equals_int(bufPerfectFit[2], 0x55 , "calling pattern_memset with pattern that fits buffer perfectly writes the 3rd byte correctly to the buffer: buffer[2] = 55");
    test_equals_int(bufPerfectFit[3], 0x44 , "calling pattern_memset with pattern that fits buffer perfectly writes the 4th byte correctly to the buffer: buffer[3] = 44");
    test_equals_int(bufPerfectFit[4], 0x33 , "calling pattern_memset with pattern that fits buffer perfectly writes the 5th byte correctly to the buffer: buffer[4] = 33");
    test_equals_int(bufPerfectFit[5], 0x22 , "calling pattern_memset with pattern that fits buffer perfectly writes the 6th byte correctly to the buffer: buffer[5] = 22");
    test_equals_int(bufPerfectFit[6], 0x11 , "calling pattern_memset with pattern that fits buffer perfectly writes the 7th byte correctly to the buffer: buffer[6] = 11");
    test_equals_int(bufPerfectFit[7], 0x00 , "calling pattern_memset with pattern that fits buffer perfectly writes the 8th byte correctly to the buffer: buffer[7] = 00");

    unsigned char bufOneByteLarger[sizeof(pat) + 1];
    pattern_memset(bufOneByteLarger, pat, sizeof(bufOneByteLarger));
    test_equals_int(bufOneByteLarger[0], 0x77 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 1st byte correctly to the buffer: buffer[0] = 77");
    test_equals_int(bufOneByteLarger[1], 0x66 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 2nd byte correctly to the buffer: buffer[1] = 66");
    test_equals_int(bufOneByteLarger[2], 0x55 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 3rd byte correctly to the buffer: buffer[2] = 55");
    test_equals_int(bufOneByteLarger[3], 0x44 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 4th byte correctly to the buffer: buffer[3] = 44");
    test_equals_int(bufOneByteLarger[4], 0x33 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 5th byte correctly to the buffer: buffer[4] = 33");
    test_equals_int(bufOneByteLarger[5], 0x22 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 6th byte correctly to the buffer: buffer[5] = 22");
    test_equals_int(bufOneByteLarger[6], 0x11 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 7th byte correctly to the buffer: buffer[6] = 11");
    test_equals_int(bufOneByteLarger[7], 0x00 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 8th byte correctly to the buffer: buffer[7] = 00");
    test_equals_int(bufOneByteLarger[8], 0x77 , "calling pattern_memset with buffer that is one byte larger than pattern writes the 9th byte correctly to the buffer: buffer[8] = 77");

    unsigned char bufThreePatternSize[3 * sizeof(pat)];
    pattern_memset(bufThreePatternSize, pat, sizeof(bufThreePatternSize));
    test_equals_int(bufThreePatternSize[0], 0x77 , "calling pattern_memset with buffer that is three times pattern size writes the 1st byte correctly to the buffer: buffer[0] = 77");
    test_equals_int(bufThreePatternSize[1], 0x66 , "calling pattern_memset with buffer that is three times pattern size writes the 2nd byte correctly to the buffer: buffer[1] = 66");
    test_equals_int(bufThreePatternSize[2], 0x55 , "calling pattern_memset with buffer that is three times pattern size writes the 3rd byte correctly to the buffer: buffer[2] = 55");
    test_equals_int(bufThreePatternSize[3], 0x44 , "calling pattern_memset with buffer that is three times pattern size writes the 4th byte correctly to the buffer: buffer[3] = 44");
    test_equals_int(bufThreePatternSize[4], 0x33 , "calling pattern_memset with buffer that is three times pattern size writes the 5th byte correctly to the buffer: buffer[4] = 33");
    test_equals_int(bufThreePatternSize[5], 0x22 , "calling pattern_memset with buffer that is three times pattern size writes the 6th byte correctly to the buffer: buffer[5] = 22");
    test_equals_int(bufThreePatternSize[6], 0x11 , "calling pattern_memset with buffer that is three times pattern size writes the 7th byte correctly to the buffer: buffer[6] = 11");
    test_equals_int(bufThreePatternSize[7], 0x00 , "calling pattern_memset with buffer that is three times pattern size writes the 8th byte correctly to the buffer: buffer[7] = 00");
    test_equals_int(bufThreePatternSize[8], 0x77 , "calling pattern_memset with buffer that is three times pattern size writes the 9th byte correctly to the buffer: buffer[8] = 77");
    test_equals_int(bufThreePatternSize[9], 0x66 , "calling pattern_memset with buffer that is three times pattern size writes the 10th byte correctly to the buffer: buffer[9] = 66");
    test_equals_int(bufThreePatternSize[10], 0x55 , "calling pattern_memset with buffer that is three times pattern size writes the 11th byte correctly to the buffer: buffer[10] = 55");
    test_equals_int(bufThreePatternSize[11], 0x44 , "calling pattern_memset with buffer that is three times pattern size writes the 12th byte correctly to the buffer: buffer[11] = 44");
    test_equals_int(bufThreePatternSize[12], 0x33 , "calling pattern_memset with buffer that is three times pattern size writes the 13th byte correctly to the buffer: buffer[12] = 33");
    test_equals_int(bufThreePatternSize[13], 0x22 , "calling pattern_memset with buffer that is three times pattern size writes the 14th byte correctly to the buffer: buffer[13] = 22");
    test_equals_int(bufThreePatternSize[14], 0x11 , "calling pattern_memset with buffer that is three times pattern size writes the 15th byte correctly to the buffer: buffer[14] = 11");
    test_equals_int(bufThreePatternSize[15], 0x00 , "calling pattern_memset with buffer that is three times pattern size writes the 16th byte correctly to the buffer: buffer[15] = 00");
    test_equals_int(bufThreePatternSize[16], 0x77 , "calling pattern_memset with buffer that is three times pattern size writes the 17th byte correctly to the buffer: buffer[16] = 77");
    test_equals_int(bufThreePatternSize[17], 0x66 , "calling pattern_memset with buffer that is three times pattern size writes the 18th byte correctly to the buffer: buffer[17] = 66");
    test_equals_int(bufThreePatternSize[18], 0x55 , "calling pattern_memset with buffer that is three times pattern size writes the 19th byte correctly to the buffer: buffer[18] = 55");
    test_equals_int(bufThreePatternSize[19], 0x44 , "calling pattern_memset with buffer that is three times pattern size writes the 20th byte correctly to the buffer: buffer[19] = 44");
    test_equals_int(bufThreePatternSize[20], 0x33 , "calling pattern_memset with buffer that is three times pattern size writes the 21st byte correctly to the buffer: buffer[20] = 33");
    test_equals_int(bufThreePatternSize[21], 0x22 , "calling pattern_memset with buffer that is three times pattern size writes the 22nd byte correctly to the buffer: buffer[21] = 22");
    test_equals_int(bufThreePatternSize[22], 0x11 , "calling pattern_memset with buffer that is three times pattern size writes the 23rd byte correctly to the buffer: buffer[22] = 11");
    test_equals_int(bufThreePatternSize[23], 0x00 , "calling pattern_memset with buffer that is three times pattern size writes the 24th byte correctly to the buffer: buffer[23] = 00");

    unsigned char bufThreePatternSizePlusOne[3 * sizeof(pat) + 1];
    pattern_memset(bufThreePatternSizePlusOne, pat, sizeof(bufThreePatternSizePlusOne));
    test_equals_int(bufThreePatternSizePlusOne[0], 0x77 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 1st byte correctly to the buffer: buffer[0] = 77");
    test_equals_int(bufThreePatternSizePlusOne[1], 0x66 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 2nd byte correctly to the buffer: buffer[1] = 66");
    test_equals_int(bufThreePatternSizePlusOne[2], 0x55 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 3rd byte correctly to the buffer: buffer[2] = 55");
    test_equals_int(bufThreePatternSizePlusOne[3], 0x44 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 4th byte correctly to the buffer: buffer[3] = 44");
    test_equals_int(bufThreePatternSizePlusOne[4], 0x33 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 5th byte correctly to the buffer: buffer[4] = 33");
    test_equals_int(bufThreePatternSizePlusOne[5], 0x22 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 6th byte correctly to the buffer: buffer[5] = 22");
    test_equals_int(bufThreePatternSizePlusOne[6], 0x11 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 7th byte correctly to the buffer: buffer[6] = 11");
    test_equals_int(bufThreePatternSizePlusOne[7], 0x00 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 8th byte correctly to the buffer: buffer[7] = 00");
    test_equals_int(bufThreePatternSizePlusOne[8], 0x77 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 9th byte correctly to the buffer: buffer[8] = 77");
    test_equals_int(bufThreePatternSizePlusOne[9], 0x66 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 10th byte correctly to the buffer: buffer[9] = 66");
    test_equals_int(bufThreePatternSizePlusOne[10], 0x55 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 11th byte correctly to the buffer: buffer[10] = 55");
    test_equals_int(bufThreePatternSizePlusOne[11], 0x44 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 12th byte correctly to the buffer: buffer[11] = 44");
    test_equals_int(bufThreePatternSizePlusOne[12], 0x33 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 13th byte correctly to the buffer: buffer[12] = 33");
    test_equals_int(bufThreePatternSizePlusOne[13], 0x22 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 14th byte correctly to the buffer: buffer[13] = 22");
    test_equals_int(bufThreePatternSizePlusOne[14], 0x11 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 15th byte correctly to the buffer: buffer[14] = 11");
    test_equals_int(bufThreePatternSizePlusOne[15], 0x00 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 16th byte correctly to the buffer: buffer[15] = 00");
    test_equals_int(bufThreePatternSizePlusOne[16], 0x77 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 17th byte correctly to the buffer: buffer[16] = 77");
    test_equals_int(bufThreePatternSizePlusOne[17], 0x66 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 18th byte correctly to the buffer: buffer[17] = 66");
    test_equals_int(bufThreePatternSizePlusOne[18], 0x55 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 19th byte correctly to the buffer: buffer[18] = 55");
    test_equals_int(bufThreePatternSizePlusOne[19], 0x44 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 20th byte correctly to the buffer: buffer[19] = 44");
    test_equals_int(bufThreePatternSizePlusOne[20], 0x33 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 21st byte correctly to the buffer: buffer[20] = 33");
    test_equals_int(bufThreePatternSizePlusOne[21], 0x22 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 22nd byte correctly to the buffer: buffer[21] = 22");
    test_equals_int(bufThreePatternSizePlusOne[22], 0x11 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 23rd byte correctly to the buffer: buffer[22] = 11");
    test_equals_int(bufThreePatternSizePlusOne[23], 0x00 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 24th byte correctly to the buffer: buffer[23] = 00");
    test_equals_int(bufThreePatternSizePlusOne[24], 0x77 , "calling pattern_memset with buffer that is three times pattern size + 1 writes the 25th byte correctly to the buffer: buffer[24] = 77");

     return test_end();
    return 0;
}
