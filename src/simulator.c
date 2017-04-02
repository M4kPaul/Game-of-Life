#include "simulator.h"

void *PngSave(void *arguments) {
    threadData *args;
    args = (threadData *)arguments;

    WriteGridToPng(&args->grid, args->fileName);

    pthread_exit(NULL);
}

int Simulate(grid_t *grid1, int numberOfGenerations, int type) {
    int i, j;
    grid_t grid2;
    threadData data;
    int responseCode;
    pthread_t threads[THREADS];

    MakeGrid(&grid2, grid1->width, grid1->height);
    MakeGrid(&data.grid, grid1->width, grid1->height);

    for (i = 1; i <= numberOfGenerations; i++) {
        if (i % 2) {
            NextGen(grid1, &grid2, type);
        } else {
            NextGen(&grid2, grid1, type);
        }

        data.grid = (i % 2) ? grid2 : *grid1;
        sprintf(data.fileName, "..\\output\\multiThreadTest\\%05d.png", i); /* TODO string size in threadData */

        if (MULTITHREADING) {
            responseCode = pthread_create(&threads[i % THREADS], NULL, PngSave, (void *)&data);
            if (responseCode) {
                fprintf(stderr, "simulator.c: Error - pthread_create() return code: %d\n", responseCode);

                return EXIT_FAILURE;
            }
        } else {
            WriteGridToPng(&data.grid, data.fileName);
        }

        if (MULTITHREADING && !(i % THREADS)) {
            for (j = 0; j < THREADS; j++) {
                pthread_join(threads[j], NULL);
            }
        }
    }


    return EXIT_SUCCESS;
}

void TransferBorders(grid_t *grid) {
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
}
