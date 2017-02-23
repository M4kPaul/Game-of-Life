#include <stdio.h>
                                                                   // +2 dla ramki żeby if'ami się nie bawić
#define GRID_H 32                                                  // wysokość
#define GRID_W 32                                                  // szerokość
#define NUMBER_OF_GENERATIONS 1000                                 // chyba za długa nazwa

void ClrArr(int arr[GRID_H][GRID_W]);                              // wypełnia zerami
void InitArr(int arr[GRID_H][GRID_W], char *in);                   // ładuje wejście
void NextGen(int curr[GRID_H][GRID_W], int next[GRID_H][GRID_W]);  // tworzy kolejną generację
void Print(int arr[GRID_H][GRID_W]);                               // wyświetla tablicę
void Simulate(int arr1[GRID_H][GRID_W], int arr2[GRID_H][GRID_W]); // rozpoczyna symulacje

int main(int argc, char *argv[]) {
  // glider - szybowiec
  char *in = "010000000000000000000000000000"
             "001000000000000000000000000000"
             "111000000000000000000000000000";

  int arr1[GRID_H][GRID_W];
  ClrArr(arr1);
  InitArr(arr1, in);

  int arr2[GRID_H][GRID_W];
  ClrArr(arr2);

  Simulate(arr1, arr2);

  return 0;
}

void ClrArr(int arr[GRID_H][GRID_W]) {
  int i, j;
  for (i = 0; i < GRID_H; i++) {
    for (j = 0; j < GRID_W; j++) {
      arr[i][j] = 0;
    }
  }
}

void InitArr(int arr[GRID_H][GRID_W], char *in) {
  int i, j, k = 0;
  for (i = 1; i < GRID_H - 1; i++) {
    for (j = 1; j < GRID_W - 1; j++) {
      if (in[k] != '\0') {
        arr[i][j] = in[k++] - '0';
      } else {
        k = -1;
        break;
      }
    }
    if (k == -1) {
      break;
    }
  }
}

void NextGen(int curr[GRID_H][GRID_W], int next[GRID_H][GRID_W]) {
  int i, j, k, l;
  for (i = 1; i < GRID_H - 1; i++) {
    for (j = 1; j < GRID_W - 1; j++) {
      int neighbours = 0;
      for (k = -1; k <= 1; k++) {
        for (l = -1; l <= 1; l++) {
          neighbours += curr[i + k][j + l];
        }
      }
      neighbours -= curr[i][j];
      if ((curr[i][j] == 1 && (neighbours == 2 || neighbours == 3))
          || (curr[i][j] == 0 && neighbours == 3)) {
        next[i][j] = 1;
      }
      else { // od razu czyści
        next[i][j] = 0;
      }
    }
  }
}

void Print(int arr[GRID_H][GRID_W]) {
  int i, j;
  for (i = 1; i < GRID_H - 1; i++) {
    for (j = 1; j < GRID_W - 1; j++) {
      printf(arr[i][j] == 1 ? "o" : " ");
    }
    printf("\n");
  }
}

void Simulate(int arr1[GRID_H][GRID_W], int arr2[GRID_H][GRID_W]) {
  int cState = 1; // obecna tablica

  int i;
  for (i = 0; i < NUMBER_OF_GENERATIONS; i++) {
    switch (cState) {
      case 1: {
        Print(arr1);
        NextGen(arr1, arr2);
        cState = 2;
        break;
      }
      case 2: {
        Print(arr2);
        NextGen(arr2, arr1);
        cState = 1;
        break;
      }
    }
    getchar();
    system("cls");
  }
}
