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
        print_grid( (i % 2) ? &grid2 : grid1 );
        getchar();
    }
}

void NextGen(grid_t *grid1, grid_t *grid2, int type) {
    int i, j, n;
    for (i = 1; i <= grid1->height; i++) {
        for (j = 1; j <= grid1->width; j++) {
            n = Neighbours(grid1, i, j, type);
            if ((grid1->data[i][j] && (n == 2 || n == 3))
              || (grid1->data[i][j] == 0 && n == 3)) {
                grid2->data[i][j] = 1;
            } else { /* clears past gen */ 
                grid2->data[i][j] = 0;
            }
        }
    }
}
