#ifndef NEIGHBOURHOODS_H_
#define NEIGHBOURHOODS_H_

#include <stdio.h>

#include "grid.h"

int Neighbours(grid_t *grid, int y, int x, char type);

int Moore(grid_t *grid, int y, int x);

int Neumann(grid_t *grid, int y, int x);

#endif /* NEIGHBOURHOODS_H_ */
