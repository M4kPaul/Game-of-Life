#include "grid.h"

grid_t makeGrid(grid_t grid, int rows, int columns) {
	grid = malloc(sizeof *grid);
	grid->data = malloc((rows * columns) * sizeof *grid->data);
	
	grid->columns = columns;
	grid->rows = rows;
	
	return grid;
}

void printGrid(grid_t grid) {
	int i, j;
	for(i = 0; i < grid->rows; i++) {
		for(j = 0; j < grid->columns; j++) {
			printf("%d ", grid->data[i * grid->columns + j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	grid_t curGrid;
	
	/*
	 * nie może być samo makeGrid, bo grid_t jest wskaznikiem, 
	 * wiec curGrid = null przy deklaracji i trzeba mu przekazac
	 * wskaznik na zaalokowano pamiec, to tak jakbys mial
	 * jakies watpliwosci
	*/
	curGrid = makeGrid(curGrid, 3, 5);
	
	curGrid->data[2] = 2;
	curGrid->data[3] = 3;
	curGrid->data[5] = 5;
	curGrid->data[7] = 7;
	curGrid->data[11] = 2;
	
	printGrid(curGrid);
	
	return 0;
}
