#define _GNU_SOURCE

#include "testlib.h"
#include "rendering.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


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


void test_wrapper_print_image(const struct line *line, const char *drawables, const char *color_codes, int num_lines) {
    for(int i = 0; i < num_lines; ++i) {
        test_wrapper_print_line(line + i, drawables, color_codes);
    }
}

void test(const struct line *image, const char *drawables, const char *color_codes, int num_lines) {
    char reference_storage[4096] = {};
    FILE *reference_stdout = fmemopen(reference_storage, sizeof(reference_storage), "w+");
    if (!reference_stdout) {
        fprintf(stderr, "something went really wrong when preparing the tests\n");
        exit(1);
    }
    stdout = reference_stdout;

    test_wrapper_print_image(image, drawables, color_codes, num_lines);
    fflush(stdout);

    char backing_storage[4096] = {};
    FILE *wrapped_stdout = fmemopen(backing_storage, sizeof(backing_storage), "w+");
    if (!wrapped_stdout) {
        fprintf(stderr, "something went really wrong when preparing the tests\n");
        exit(1);
    }
    stdout = wrapped_stdout;
    print_image(image, drawables, color_codes, num_lines);
    fflush(stdout);

    for (int i = 0; i < image->line_prefix; ++i) {
        test_equals_int(backing_storage[i], ' ', "the prefix should be spaces");
    }
    bool found = false;
    for(int i = 0, j = 0; backing_storage[i] && reference_storage[j]; ++i, ++j) {
        while(backing_storage[i] == ' ' && reference_storage[j] == '\n') ++i;
        if (backing_storage[i] != reference_storage[j]) {
            test_equals_string(backing_storage + image->line_prefix, reference_storage + image->line_prefix, "the filled bytes should match");
            found = true;
            break;
        }
    }
    if (!found)
        // just make the test counter actually correct by using a pseudo test. We actually do the test manually
        test_equals_int(0, 0, "the filled bytes should match");

    int actual_length = strlen(backing_storage);
    test_equals_int(backing_storage[actual_length], '\0', "the remaining bytes should be zero");

    fclose(reference_stdout);
    fclose(wrapped_stdout);
}

int main() {
    FILE *real_stdout = stdout;
    override_output_fstream((void*) real_stdout);

    test_start("you print the whole image correctly.");
    test_plan(11);

    test(first_image, drawables, color_codes, 5);
    test(second_image, drawables, color_codes2, 20);

    return test_end();
}

