#ifndef GRID_H_
#define GRID_G_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int rows;
	int columns;
	int *data;
} *grid_t;

grid_t makeGrid(grid_t grid, int rows, int columns);

/* funkcja do debugowania */
void printGrid(grid_t grid);

#endif /* GRID_H_ */
