#ifndef RENDERING_H
#define RENDERING_H

#include <stdint.h>

struct line {
    // how many characters to parse
    int line_length;
    // how many spaces to insert at the beginning
    int line_prefix;
    // how many spaces to insert at the end
    int line_postfix;
    // where to start reading
    const uint8_t *line_pointer;
};

int color_at(const uint8_t *data, int index);
void print_line(const struct line *line, const char *drawables, const char *color_codes);
void print_image(const struct line *line, const char *drawables, const char *color_codes, int num_lines);

// reference the data that you shall decode
extern const char drawables[];
extern const char color_codes[];
extern const char color_codes2[];
extern const uint8_t first_image_data[];
extern const struct line first_image[];
extern const uint8_t second_image_data[];
extern const struct line second_image[];

#endif
