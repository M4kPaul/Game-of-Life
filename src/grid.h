#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef GAME_OF_LIFE_GRID_H
#define GAME_OF_LIFE_GRID_H

typedef struct {
    int width;
    int height;
    int **data;
} grid_t;

int make_grid(grid_t *grid, int width, int height);

void print_grid(grid_t *grid);

void print_grid_with_borders(grid_t *grid);

#endif //GAME_OF_LIFE_GRID_H
