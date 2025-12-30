#include <stdio.h>

#include "rendering.h"

/*!
 * \brief print the 4 bits stored at location "index" in the array data
 * \param data all data elements
 * \param index the index into the data element
 * \attention even indices use the upper bits (7:4), odd indices use the lower bits (3:0)
 */
int color_at(const uint8_t *data, int index) {
    (void) data;
    (void) index;

    // TODO: return data encoded at 4-bit-index into the data array
    return 0;
}

/*!
 * \brief print a line
 * \param line describes the complete line
 * \param drawables the array which provides characters to draw at each position
 * \param color_codes a number to print into the shell color code directives
 */
void print_line(const struct line *line, const char *drawables, const char *color_codes) {
    (void) line;
    (void) drawables;
    (void) color_codes;
    // TODO: print a single line, including leading spaces
}

/*!
 * \brief print a complete image, by repeatidly calling \ref print_line
 * \param image pointer to first line in image array
 * \param drawables the array which provides characters to draw at each position
 * \param color_codes a number to print into the shell color code directives
 * \param num_lines how many elements are in the image array
 */
void print_image(const struct line *image, const char *drawables, const char *color_codes, int num_lines) {
    (void) image;
    (void) drawables;
    (void) color_codes;
    (void) num_lines;
    // TODO print a complete image
}
