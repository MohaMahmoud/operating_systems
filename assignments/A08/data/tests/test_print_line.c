#define _GNU_SOURCE

#include "testlib.h"
#include "rendering.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int test_wrapper_color_at(const uint8_t *data, int index) {
    uint8_t byte = data[index / 2];
    if (index & 1)
        return byte & 0xf;
    else
        return (byte >> 4) & 0xf;
}

static void test_wrapper_print_line(const struct line *line, const char *drawables, const char *color_codes) {
    for (int i = 0; i < line->line_prefix; ++i)
        putchar(' ');
    for (int i = 0; i < line->line_length; ++i) {
        char color_code = color_codes[test_wrapper_color_at(line->line_pointer, i)];
        printf("\e[%dm", (int) color_code);
        char drawable = drawables[test_wrapper_color_at(line->line_pointer, i)];
        putchar(drawable);
    }
    putchar('\n');
}


int main() {
    FILE *real_stdout = stdout;
    override_output_fstream((void*) real_stdout);

    char reference_storage[4096] = {};
    FILE *reference_stdout = fmemopen(reference_storage, sizeof(reference_storage), "w+");
    if (!reference_stdout) {
        fprintf(stderr, "something went really wrong when preparing the tests\n");
        exit(1);
    }
    stdout = reference_stdout;

    test_wrapper_print_line(second_image, drawables, color_codes2);
    fflush(stdout);


    char backing_storage[4096] = {};
    FILE *wrapped_stdout = fmemopen(backing_storage, sizeof(backing_storage), "w+");
    if (!wrapped_stdout) {
        fprintf(stderr, "something went really wrong when preparing the tests\n");
        exit(1);
    }
    stdout = wrapped_stdout;

    test_start("you print a line correctly.");
    test_plan(24);

    print_line(second_image, drawables, color_codes2);
    fflush(stdout);

    for (int i = 0; i < second_image->line_prefix; ++i) {
        test_equals_int(backing_storage[i], ' ', "the prefix should be spaces");
    }
    int actual_length = strlen(backing_storage);
    int offset = 0;
    for (int i = 0; i + offset < actual_length - second_image->line_prefix; ++i) {
        while (backing_storage[second_image->line_prefix + offset + i] == ' ' && reference_storage[second_image->line_prefix + i] == '\n') ++offset;
        test_equals_int(backing_storage[second_image->line_prefix + offset + i], reference_storage[second_image->line_prefix + i], "the filled bytes should match");
    }
    test_equals_int(backing_storage[actual_length], '\0', "the remaining bytes should be zero");

    return test_end();
}

