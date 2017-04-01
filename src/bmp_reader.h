#ifndef BMP_READER_H_
#define BMP_READER_H_

#include <stdio.h>

#include "grid.h"

int ReadBMP(FILE *fn, grid_t *grid);

#endif /* BMP_READER_H_ */
