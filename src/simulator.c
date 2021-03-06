#include "simulator.h"

void *Thread(void *arguments) {
    threadData *args;
    args = (threadData *)arguments;

    if (Write(&args->grid, args->info) == EXIT_FAILURE) {
        fprintf(stderr, "simulator.c: Warning - failed to save generation number: %d\n", args->info->generation);
    }

    pthread_exit(NULL);
}

int Simulate(grid_t *grid1, char neighbourhoodType, outputInfo *info) {
    int i, j;
    grid_t grid2;
    threadData data;
    int responseCode;
    int numberOfThreads;
    int numberOfGenerations;
    pthread_t threads[info->numberOfThreads];

    numberOfThreads = info->numberOfThreads;
    numberOfGenerations = info->numberOfGenerations;

    data.grid = *grid1;
    info->generation = 0;
    if(Write(&data.grid, info) == EXIT_FAILURE) {
        fprintf(stderr, "simulator.c: Warning - failed to save generation number: %d\n", 0);
    }

    MakeGrid(&grid2, grid1->width, grid1->height);
    MakeGrid(&data.grid, grid1->width, grid1->height);

    for (i = 1; i <= numberOfGenerations; i++) {
        if (i % 2) {
            responseCode = NextGen(grid1, &grid2, neighbourhoodType);
        } else {
            responseCode = NextGen(&grid2, grid1, neighbourhoodType);
        }

        if (responseCode == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }

        data.grid = (i % 2) ? grid2 : *grid1;
        info->generation = i;

        if (numberOfThreads > 0) {
            data.info = info;
            responseCode = pthread_create(&threads[i % numberOfThreads], NULL, Thread, (void *)&data);
            if (responseCode) {
                fprintf(stderr, "simulator.c: Error - pthread_create() return code: %d\n", responseCode);
                return EXIT_FAILURE;
            }
        } else {
            if(Write(&data.grid, info) != EXIT_SUCCESS) {
                fprintf(stderr, "simulator.c: Warning - failed to save generation number: %d\n", i);
            }
        }

        if (numberOfThreads > 0 && !(i % numberOfThreads)) {
            for (j = 0; j < numberOfThreads; j++) {
                responseCode = pthread_join(threads[j], NULL);
                if (responseCode != 0) {
                    fprintf(stderr, "simulator.c: Error - pthread_join() return code: %d\n", responseCode);
                    return EXIT_FAILURE;
                }
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

int NextGen(grid_t *grid1, grid_t *grid2, char type) {
    int i, j, n;
    for (i = 0; i <= grid1->height + 1; i++) {
        for (j = 0; j <= grid1->width + 1; j++) {
            n = Neighbours(grid1, i, j, type);
            if (n < 0) {
                return EXIT_FAILURE;
            }
            if ((grid1->data[i][j] && (n == 2 || n == 3))
                || (grid1->data[i][j] == 0 && n == 3)) {
                grid2->data[i][j] = 1;
            } else {
                grid2->data[i][j] = 0;
            }
        }
    }
    TransferBorders(grid2);

    return EXIT_SUCCESS;
}
