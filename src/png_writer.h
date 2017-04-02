#ifndef PNG_WRITER_H_
#define PNG_WRITER_H_

#include <stdlib.h>
#include <png.h>

#include "bitmap.h"
#include "grid.h"

#define PNG_DEPTH_DEFAULT 8

static void ConvertGridToBitmap(grid_t *grid, bitmap_t *bitmap);

int WriteGridToPng(grid_t *grid, char *file_name);

#endif /* PNG_WRITER_H_ */
