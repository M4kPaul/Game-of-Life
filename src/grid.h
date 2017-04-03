#ifndef GRID_H_
#define GRID_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int **data;
} grid_t;

int MakeGrid(grid_t *grid, int width, int height);

void DestroyGrid(grid_t *grid);

#endif /* GRID_H_ */
