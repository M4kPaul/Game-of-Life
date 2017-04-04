#ifndef IOCONTROL_H_
#define IOCONTROL_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp_reader.h"
#include "grid.h"
#include "png_reader.h"
#include "png_writer.h"

typedef struct {
    char *path;
    int generation;
    int numberOfGenerations;
    char outputMethod;
    int numberOfThreads;
} outputInfo;

int Read(char inputMethod, char *fileName, grid_t *grid);

char *FileNameBuilder(outputInfo *info);

int Write(grid_t *grid, outputInfo *info);

int StrToInt(char *number);

int CheckArgs(int argc, char **argv);

int OutputInfoParser(outputInfo *info, int argc, char **argv);

#endif /* IOCONTROL_H_ */
