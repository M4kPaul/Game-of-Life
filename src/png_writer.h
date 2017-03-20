#include <stdlib.h>
#include <stdint.h>

#include "grid.h"
#include "png.h"

#ifndef GAME_OF_LIFE_PNG_WRITER_H
#define GAME_OF_LIFE_PNG_WRITER_H

#define PNG_DEPTH_DEFAULT 8
#define PIXEL_SIZE_DEFAULT 3

static int convert_grid_to_bitmap(grid_t *grid, png_bytepp bitmap);

int write_grid_to_png(grid_t *grid, char *file_name);

#endif //GAME_OF_LIFE_PNG_WRITER_H
