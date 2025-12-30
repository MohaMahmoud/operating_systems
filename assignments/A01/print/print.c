#include "print.h"

#include <stddef.h>
#include <stdio.h>

void print_line(int64_t number, char *string)
{
    if (string == NULL) {
        return;
    }

    printf("%" PRId64 " %s\n", number, string);
}
