#include "grid.h"

int MakeGrid(grid_t *grid, int width, int height) {
    int y;

    grid->width = width;
    grid->height = height;

    width += 2;
    height += 2;

    grid->data = calloc(height * sizeof(int), sizeof(int));

    for (y = 0; y < height; y++) {
        grid->data[y] = calloc(width * sizeof(int), sizeof(int));
        if (!grid->data[y]) {
            fprintf(stderr, "grid.c: memory cannot be allocated for the grid\n");

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void DestroyGrid(grid_t *grid) {
    int y;

    for(y = 0; y < grid->height + 2; y++) {
        free(grid->data[y]);
    }
    free(grid->data);
}
