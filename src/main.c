#include <stdio.h>
#include <time.h>

#include "grid.h"
#include "png_reader.h"
#include "png_writer.h"
#include "simulator.h"

int main(int argc, char **argv) {
    clock_t start = clock();

    char *file_name_in = argc > 1 ? argv[1] : stdin;
    char *file_name_out = argc > 2 ? argv[2] : stdin;

    grid_t grid;

    if (read_png_to_grid(file_name_in, &grid)) {
//        TODO destroy_grid();
        return 1;
    }

    if (Simulate(&grid, 100000, 1)) {
//        TODO destroy_grid(); ?
        return 1;
    }

    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);

    /*
    if (write_grid_to_png(&grid, file_name_out)) {
//        TODO destroy_grid();
        return 1;
    }

//    TODO destroy_grid();
    */

    return 0;
}
