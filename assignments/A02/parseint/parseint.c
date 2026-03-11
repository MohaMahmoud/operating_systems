#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int parseDecimalChar(char c)
{
    if (c >= '0' && c <= '9'){return c - '0';} 
    else {return -1;}
}

/*
 * Parses a non-negative integer, interpreted as octal when starting with 0,
 * decimal otherwise. Returns -1 on error.
 */
int parseInt(char *string) {
    if (string == 0 || string[0] == '\0') {
        return -1;
    }

    int result = 0;
    int base = 10; 

    // If it starts with '0', it's an octal number
    if (string[0] == '0') {
        base = 8;
    }

    // Loop until the null-terminator is reached
    for (int index = 0; string[index] != '\0'; index++) {
        int digit = parseDecimalChar(string[index]);

        // If it's not a valid decimal char OR it's too large for the current base (e.g., '8' or '9' in base 8)
        if (digit == -1 || digit >= base) {
            return -1;
        }

        // Shift the previous result by the base and add the new digit
        result = (result * base) + digit;
    }

    return result;
}
