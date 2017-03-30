#include <stdio.h>

#include "grid.h"
#include "png_reader.h"
//#include "png_writer.h"
#include "simulator.h"

int main(int argc, char **argv) {
    char *file_name_in = argc > 1 ? argv[1] : stdin;
//    char *file_name_out = argc > 2 ? argv[2] : stdin;

    grid_t grid;

    if(read_png_to_grid(file_name_in, &grid)) {
//        TODO destroy_grid();

        return 1;
    }

    Simulate(&grid, 100, 1);
//    print_grid(&grid);
//    print_grid_with_borders(&grid);

/*    if(write_grid_to_png(&grid, file_name_out)) {dir
 *
//        TODO destroy_grid();

        return 1;
    }
*/
//    TODO destroy_grid();
    return 0;
}
