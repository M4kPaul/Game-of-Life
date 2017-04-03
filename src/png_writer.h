#ifndef PNG_WRITER_H_
#define PNG_WRITER_H_

#include <stdlib.h>
#include <stdint.h>

#include "grid.h"
#include "png.h"
#include "png_reader.h"

#define PNG_DEPTH_DEFAULT 8
#define PIXEL_SIZE_DEFAULT 3

static int ConvertGridToBitmap(grid_t *grid, png_bytepp bitmap);

static void DestroyBitmap(png_bytepp bitmap, int height);

int WriteGridToPng(char *file_name, grid_t *grid);

#endif /* PNG_WRITER_H_ */
