#include "rendering.h"

#include <stdio.h>

int main()
{
    uint8_t value = 0x20;
    printf("decoding a '/' to '%c'\n", drawables[color_at(&value, 0)]);
    printf("and now for the real thing:\n\n");

    print_image(first_image, drawables, color_codes2, 5);
    printf("\e[0m\n\n=========================================\n\n");
    print_image(second_image, drawables, color_codes, 20);
}

