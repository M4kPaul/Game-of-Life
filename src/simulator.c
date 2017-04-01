#include "simulator.h"

void Simulate(grid_t *grid1, int numberOfGenerations, int type) {
    int i;
    grid_t grid2;

    make_grid(&grid2, grid1->width, grid1->height);

    for (i = 0; i < numberOfGenerations; i++) {
        if (i % 2 == 0) {
            NextGen(grid1, &grid2, type);
        } else {
            NextGen(&grid2, grid1, type);
        }
    }
}

void TransferBorders(grid_t *grid) { /* copy over only if existed in border */
    int i;
    for (i = 1; i <= grid->width; i++) {
        if (grid->data[0][i]) {
            grid->data[0][i] = grid->data[1][i];                           /* top   */
        }
        if (grid->data[grid->height + 1][i]) {
            grid->data[grid->height + 1][i] = grid->data[grid->height][i]; /* down  */
        }
    }
    for (i = 0; i <= grid->height; i++) { /* corners++ */
        if (grid->data[i][0]) {
            grid->data[i][0] = grid->data[i][1];                           /* left  */
        }
        if (grid->data[i][grid->width + 1]) {
            grid->data[i][grid->width + 1] = grid->data[i][grid->width];   /* right */
        }
    }
}

void NextGen(grid_t *grid1, grid_t *grid2, int type) {
    int i, j, n;
    for (i = 0; i <= grid1->height + 1; i++) {
        for (j = 0; j <= grid1->width + 1; j++) {
            n = Neighbours(grid1, i, j, type);
            if ((grid1->data[i][j] && (n == 2 || n == 3))
                || (grid1->data[i][j] == 0 && n == 3)) {
                grid2->data[i][j] = 1;
            } else {
                grid2->data[i][j] = 0;
            }
        }
    }
    TransferBorders(grid2);
//    print_grid(grid2); /* TODO zapis */
}
