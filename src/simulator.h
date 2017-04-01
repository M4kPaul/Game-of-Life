#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <stdio.h>

#include "grid.h"
#include "neighbourhoods.h"

void Simulate(grid_t *grid1, int numberOfGenerations, int type);

void TransferBorders(grid_t *grid);

void NextGen(grid_t *grid1, grid_t *grid2, int type);

#endif /* SIMULATOR_H_ */
