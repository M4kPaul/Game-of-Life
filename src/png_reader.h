#ifndef PNG_READER_H_
#define PNG_READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

#include "grid.h"

#define NUMBER_OF_CHECKED_BYTES 8
#define PIXEL_SIZE_DEFAULT 3

static int is_black(png_bytepp bitmap, int x, int y);

static int is_white(png_bytepp bitmap, int x, int y);

static int write_bitmap_to_grid(grid_t *grid, png_bytepp bitmap);

int read_png_to_grid(char *file_name, grid_t *grid);

#endif /* PNG_READER_H_ */
