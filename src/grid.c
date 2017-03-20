#include "grid.h"

int make_grid(grid_t *grid, int width, int height) {
    grid->width = width;
    grid->height = height;

    width += 2;
    height += 2;

    grid->data = malloc(height * sizeof(int));

    for(int y = 0; y < height; y++) {
        grid->data[y] = malloc(width * sizeof(int));
        if(!grid->data[y]) {
            fprintf(stderr, "grid.c: memory cannot be allocated for the grid\n");

            return EXIT_FAILURE;
        }
    }

//    for(int x = 0; x < width; x++) {
//        grid->data[0][x] = 7;
//        grid->data[height - 1][x] = 7;
//    }
//
//    for(int y = 0; y < height; y++) {
//        grid->data[y][0] = 7;
//        grid->data[y][width - 1] = 7;
//    }
//
    return EXIT_SUCCESS;
}

void print_grid(grid_t *grid) {
    for(int y = 1; y <= grid->height; y++) {
        for(int x = 1; x <= grid->width; x++) {
            printf("%d ", grid->data[y][x]);
        }
        printf("\n");
    }
}

void print_grid_with_borders(grid_t *grid) {
    for(int y = 0; y <= grid->height + 1; y++) {
        for(int x = 0; x <= grid->width + 1; x++) {
            printf("%d ", grid->data[y][x]);
        }
        printf("\n");
    }
}
