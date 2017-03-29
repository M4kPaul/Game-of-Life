#ifndef NEIGHBOURHOODS_H_
#define NEIGHBOURHOODS_H_

#include <stdio.h>

#include "grid.h"

int Neighbours(grid_t *grid, int x, int y, int type);

int Moore(grid_t *grid, int x, int y);

int Neumann(grid_t *grid, int x, int y);

#endif /* NEIGHBOURHOODS_H_ */
