#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "grid.h"
#include "neighbourhoods.h"
#include "png_writer.h"

#define MULTITHREADING 1
#define THREADS 1

typedef struct {
    grid_t grid;
    char fileName[100];
} threadData;

void *PngSave(void *arguments);

int Simulate(grid_t *grid1, int numberOfGenerations, int type);

void TransferBorders(grid_t *grid);

void NextGen(grid_t *grid1, grid_t *grid2, int type);

#endif /* SIMULATOR_H_ */
