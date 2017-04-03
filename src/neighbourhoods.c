#include "neighbourhoods.h"

int Neighbours(grid_t *grid, int y, int x, char type) {
    switch (type) {
        case 'm':
        case 'M':
            return Moore(grid, y, x);
        case 'n':
        case 'N':
            return Neumann(grid, y, x);
        default:
            fprintf(stderr, "nieghbourhoods.c: neighbourhood of type -%c does not exist\n", type);
            return -1;
    }
}

int Moore(grid_t *grid, int y, int x) {
    int i, j;
    int sum = 0;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (y + i >= 0 && y + i <= grid->height + 1
                && x + j >= 0 && x + j <= grid->width + 1) {
                sum += grid->data[y + i][x + j];
            }
        }
    }

    return sum - grid->data[y][x];
}

int Neumann(grid_t *grid, int y, int x) {
    int sum = 0;

    if (y - 1 >= 0) {
        sum += grid->data[y - 1][x]; /* top   */
    }
    if (x - 1 >= 0) {
        sum += grid->data[y][x - 1]; /* left  */
    }
    if (x + 1 <= grid->width + 1) {
        sum += grid->data[y][x + 1]; /* right */
    }
    if (y + 1 <= grid->height + 1) {
        sum += grid->data[y + 1][x]; /* down  */
    }

    return sum;
}
