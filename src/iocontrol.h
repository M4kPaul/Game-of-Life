#ifndef IOCONTROL_H_
#define IOCONTROL_H_

#include <stdio.h>

#include "bmp_reader.h"
#include "grid.h"
#include "png_reader.h"
#include "png_writer.h"

typedef struct {
    char *path;
    int generation;
    char *extension;
} outputInfo;

int Read(FILE *fileName, char* inputMethod);
int Write(grid_t *grid, outputInfo *info);

#endif /* IOCONTROL_H_ */
