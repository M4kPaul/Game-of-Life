#include <stdio.h>

#include "grid.h"
#include "iocontrol.h"
#include "simulator.h"

static char *usage =
  "                                                                                                                              \n"
  "Usage: %s -neighbourhoodType <numberOfGenerations> -inputMethod <inputFile> -outputMethod <outputPath> [-t <numberOfThreads>] \n"
  "where:                                                                                                                        \n"
  "   required:                                                                                                                  \n"
  "       neighbourhoodType - type of a neighbourhood used for counting surrounding neighbours:                                  \n"
  "           -N - von Neumann neighborhood is composed of its four adjacent cells                                               \n"
  "           -M - Moore neighborhood is composed of the eight cells which surround the central one                              \n"
  "       numberOfGenerations - number of generations (argument must be an integer from the range of <1, %d>)                    \n"
  "       inputMethod - a method of reading the 0th generation:                                                                  \n"
  "           -b - a BMP                                                                                                         \n"
  "           -n - numbers (0&1):                                                                                                \n"
  "               ...description...                                                                                              \n"
  "           -p - a PNG                                                                                                         \n"
  "       inputFile - a path of input file with its proper extension                                                             \n"
  "       outputMethod - a method of writing the nth generation:                                                                 \n"
  "           (corresponding outputMethod behaviour is equivalent as in inputMethod)                                             \n"
  "           -p - a PNG                                                                                                         \n"
  "           -n - numbers                                                                                                       \n"
  "       outputPath - a path, with system specific path separator at the end, of where to save each generation                  \n"
  "   optional:                                                                                                                  \n"
  "       -t - indicates the will of using multiple threads                                                                      \n"
  "       <numberOfThreads> - number of threads to use while saving files (positive integer)                                     \n"
  "                                                                                                                             \n";

int main(int argc, char **argv) {
    if (CheckArgs(argc, argv) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0], INT_MAX);
        return 1;
    }

    grid_t grid;
    if(Read(argv[3][1], argv[4], &grid) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0], INT_MAX);
        DestroyGrid(&grid);
        return 1;
    }

    outputInfo info;
    if (OutputInfoParser(&info, argc, argv) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0], INT_MAX);
        DestroyGrid(&grid);
        return 1;
    }

    if(Simulate(&grid, argv[1][1], &info) == EXIT_FAILURE) {
        fprintf(stderr, usage, argv[0], INT_MAX);
        DestroyGrid(&grid);
        return 1;
    }

    DestroyGrid(&grid);

    return 0;
}