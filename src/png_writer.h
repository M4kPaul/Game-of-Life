#ifndef PNG_WRITER_H_
#define PNG_WRITER_H_

#include <stdlib.h>
#include <stdint.h>

#include "grid.h"
#include "png.h"

#define PNG_DEPTH_DEFAULT 8
#define PIXEL_SIZE_DEFAULT 3

static void convert_grid_to_bitmap(grid_t *grid, png_bytepp bitmap);

int write_grid_to_png(grid_t *grid, char *file_name);

#endif /* PNG_WRITER_H_ */
