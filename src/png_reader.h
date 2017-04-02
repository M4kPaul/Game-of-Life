#ifndef PNG_READER_H_
#define PNG_READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

#include "grid.h"

#define NUMBER_OF_CHECKED_BYTES 8
#define PIXEL_SIZE_DEFAULT 3

static int IsBlack(png_bytepp bitmap, int x, int y);

static int IsWhite(png_bytepp bitmap, int x, int y);

static int WriteBitmapToGrid(grid_t *grid, png_bytepp bitmap);

static void DestroyBitmap(png_bytepp bitmap, int height);

int ReadPngToGrid(char *file_name, grid_t *grid);

#endif /* PNG_READER_H_ */
