#include <stdio.h>
                                                   /* +2 dla ramki żeby if'ami się nie bawić */
#define HEIGHT 32                                  /* wysokość                               */
#define WIDTH 32                                   /* szerokość                              */
#define NUMBER_OF_GENERATIONS 1000                 /* chyba za długa nazwa                   */

void Init(int grid[HEIGHT][WIDTH], char *in);      /* ładuje wejście           */
void NextGen(int grid[HEIGHT][WIDTH], int cState); /* tworzy kolejną generację */
void Print(int grid[HEIGHT][WIDTH], int cState);   /* wyświetla tablicę        */
void Simulate(int grid[HEIGHT][WIDTH]);            /* rozpoczyna symulacje     */

int main(int argc, char *argv[]) {
  /* glider - szybowiec */
  char *in = "010000000000000000000000000000"
	         "001000000000000000000000000000"
	         "111000000000000000000000000000";

  int grid[HEIGHT][WIDTH];
  Init(grid, in);

  Simulate(grid);

  return 0;
}

void Init(int grid[HEIGHT][WIDTH], char *in) {
  int i, j, k = 0;
  for (i = 0; i < HEIGHT; i++) {
	for (j = 0; j < WIDTH; j++) {
	  if (in[k] != '\0' && i != 0 && j != 0 
		&& i != HEIGHT- 1 && j != WIDTH - 1) {
		grid[i][j] = in[k++] - '0';
	  }
	  else {
		grid[i][j] = 0;
	  }
	}
  }
}

void NextGen(int grid[HEIGHT][WIDTH], int cState) {
  int i, j, k, l;
  for (i = 1; i < HEIGHT - 1; i++) {
	for (j = 1; j < WIDTH - 1; j++) {
	  int neighbours = 0;
	  for (k = -1; k <= 1; k++) {
		for (l = -1; l <= 1; l++) {                                      /* zlicza sąsiadów */
		  if ((k != 0 || l != 0) &&                                      /*    [?][?][?]    */
			(grid[i + k][j + l] == cState || grid[i + k][j + l] == 3)) { /*    [?][x][?]    */
			neighbours++;                                                /*    [?][?][?]    */
		  }
		}
	  }
	  if ((grid[i][j] == cState && (neighbours == 2 || neighbours == 3)) /* żywa && (2 || 3 sąsiadów) = żywa */
		|| (grid[i][j] == 0 && neighbours == 3)) {                       /* martwa && 3 sąsiadów      = żywa */
		if (grid[i][j] == 0) {
		  grid[i][j] = (cState == 1) ? 2 : 1;
		}
		else {
		  grid[i][j] = 3; /* żywa teraz i wcześniej */
		}
	  }
	}
  }
}

void Print(int grid[HEIGHT][WIDTH], int cState) {
  int i, j;
  for (i = 1; i < HEIGHT - 1; i++) {
	for (j = 1; j < WIDTH - 1; j++) {
	  if (grid[i][j] == cState || grid[i][j] == 3) {
		grid[i][j] = cState;
		printf("o");
	  }
	  else {
		printf(".");
		grid[i][j] = 0;
	  }
	}
	printf("\n");
  }
}

void Simulate(int grid[HEIGHT][WIDTH]) {
  int cState = 1; /* obecna tablica */

  int i;
  for (i = 0; i < NUMBER_OF_GENERATIONS; i++) {
	Print(grid, cState);

	NextGen(grid, cState);

	cState = (cState == 1) ? 2 : 1;

	getchar();
  }
}
