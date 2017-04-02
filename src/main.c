#include <stdio.h>
#include <string.h>
#include <time.h>

#include "grid.h"
#include "iocontrol.h"
#include "simulator.h"

static char *usage =
  "Usage: %s -neighbourhoodType <numberOfGenerations> -inputMethod <inputFile> -outputMethod <outputPath> [-g <GIF>] \n"
  "where:                                                                                                            \n"
  "   required:                                                                                                      \n"
  "       neighbourhoodType - type of a neighbourhood used for counting surrounding neighbours:                      \n"
  "           -N - von Neumann neighborhood is composed of its four adjacent cells                                   \n"
  "           -M - Moore neighborhood is composed of the eight cells which surround the central one                  \n"
  "       numberOfGenerations - number of generations to generate (argument must be an integer greater than zero)    \n"
  "       inputMethod - a method of reading the 0th generation:                                                      \n"
  "           -b - a BMP                                                                                             \n"
  "           -c - coordinates:                                                                                      \n"
  "               ...description...                                                                                  \n"
  "           -n - numbers (0&1):                                                                                    \n"
  "               ...description...                                                                                  \n"
  "           -p - a PNG                                                                                             \n"
  "       inputFile - a path of input file with its proper extension                                                 \n"
  "       outputMethod - a method of writing the nth generation:                                                     \n"
  "           -p - a PNG                                                                                             \n"
  "           ...the rest...                                                                                         \n"
  "       outputPath - a path where to save each generation                                                          \n"
  "   optional:                                                                                                      \n"
  "       -g - indicates the will of generating a GIF                                                                \n"
  "       <GIF> - file path and name with .gif extension to save                                                     \n"
  "                                                                                                                 \n";

int main(int argc, char **argv) {
    /* TODO MAIN IOCONTROL */
    clock_t start = clock();

    char *file_name_in = argc > 1 ? argv[1] : stdin;
    char *file_name_out = argc > 2 ? argv[2] : stdin;

    grid_t grid;
    /* TODO przekazywac otwarty plik ify itp   */
    /* Read(FILE *fileName, char* inputMethod) */
    if(Read(file_name_in, &grid) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0]);
        DestroyGrid(&grid);
        return 1;
    }

    outputInfo info;
    /* TODO ify do argv */
    if(Simulate(&grid, argv[2], argv[1], &info) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0]);
        DestroyGrid(&grid);
        return 1;
    }

    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);

    DestroyGrid(&grid);

    return 0;
}
