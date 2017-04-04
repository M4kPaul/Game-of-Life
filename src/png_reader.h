#ifndef PNG_READER_H_
#define PNG_READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

#include "bitmap.h"
#include "grid.h"

#define NUMBER_OF_CHECKED_BYTES 8

static void WriteBitmapToGrid(grid_t *grid, bitmap_t *bitmap);

int ReadPngToGrid(char *fileName, grid_t *grid);

#endif /* PNG_READER_H_ */
