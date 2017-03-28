#include "neighbourhoods.h"

int Neighbours(grid_t *grid, int x, int y, int type=1) {
    switch type: {
        case 1:
            return Moore(grid, x, y);
        case 2:
            return Neumann(grid, x, y);
    }
}

int Moore(grid_t *grid, int x, int y) {
    int i, j;
    int sum = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (x + i != 0 || x + i != grid->height
              || y + j != 0 || y + j != grid->width) {
                sum += grid->data[x + i][y + j];
            }
        }
    }
    return sum;
}

int Neumann(grid_t *grid, int x, int y) {
    int sum = 0;
    if (x - 1 != 0) {
        sum += grid->data[x - 1][y]; /* top   */
    }
    if (y - 1 != 0) {
        sum += grid->data[x][y - 1]; /* left  */
    }
    if (y + 1 != grid->width) {
        sum += grid->data[x][y + 1]; /* right */
    }
    if (x + 1 != grid->height) {
        sum += grid->data[x + 1][y]; /* down  */
    }
    return sum;
}
