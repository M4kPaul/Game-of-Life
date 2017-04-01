#include <stdio.h>
#include <pthread.h>

#include "grid.h"
#include "png_reader.h"
#include "png_writer.h"
#include "simulator.h"

void *inc_x(void *ptr) {
    int x = 0;
    char *message = (char *)ptr;
    while (x <= 10000) {
        printf("%s - %d\n", message, x++);
    }
}

int main(int argc, char **argv) {
    pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";

    int ret1 = pthread_create(&thread1, NULL, inc_x, (void*)message1);
    if (ret1) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", ret1);

        return 1;
    }

    int ret2 = pthread_create(&thread2, NULL, inc_x, (void*)message2);
    if (ret2) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", ret2);

        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    /*
    char *file_name_in = argc > 1 ? argv[1] : stdin;
    char *file_name_out = argc > 2 ? argv[2] : stdin;

    grid_t grid;

    if (read_png_to_grid(file_name_in, &grid)) {
//        TODO destroy_grid();
        return 1;
    }

    Simulate(&grid, 1000, 1);

    if (write_grid_to_png(&grid, file_name_out)) {
//        TODO destroy_grid();
        return 1;
    }

//    TODO destroy_grid();
    */

    return 0;
}
