#include "grid.h"

int make_grid(grid_t *grid, int width, int height) {
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

void print_grid(grid_t *grid) {
    int y, x;

    for (y = 1; y <= grid->height; y++) {
        for (x = 1; x <= grid->width; x++) {
            printf("%c ", (grid->data[y][x]) ? 'o' : ' ');
            /* printf("%d ", grid->data[y][x]); */
        }
        printf("\n");
    }
}

void print_grid_with_borders(grid_t *grid) {
    int y, x;

    for (y = 0; y <= grid->height + 1; y++) {
        for (x = 0; x <= grid->width + 1; x++) {
            printf("%c ", (grid->data[y][x]) ? 'o' : ' ');
            /* printf("%d ", grid->data[y][x]); */
        }
        printf("\n");
    }
}
