#include "png_reader.h"

static int is_black(png_bytepp bitmap, int x, int y) {
    if (bitmap[y][x] == 0 && bitmap[y][++x] == 0 && bitmap[y][++x] == 0) {
        return 1;
    }
    return 0;
}

static int is_white(png_bytepp bitmap, int x, int y) {
    if (bitmap[y][x] == 255 && bitmap[y][++x] == 255 && bitmap[y][++x] == 255) {
        return 1;
    }
    return 0;
}

static int write_bitmap_to_grid(grid_t *grid, png_bytepp bitmap) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0, i = 1; x < grid->width * PIXEL_SIZE_DEFAULT; x += 3, i++) {
            if (is_black(bitmap, x, y)) {
                grid->data[y + 1][i] = 1;
            } else if (is_white(bitmap, x, y)) {
                grid->data[y + 1][i] = 0;
            } else {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

int read_png_to_grid(char *file_name, grid_t *grid) {
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stderr, "png_reader.c: file %s cannot be open for reading\n", file_name);

        return EXIT_FAILURE;
    }

    png_bytep header = malloc(NUMBER_OF_CHECKED_BYTES * sizeof(png_bytep));
    if (!header) {
        fprintf(stderr, "png_reader.c: memory cannot be allocated for header\n");

        fclose(fp);

        return EXIT_FAILURE;
    }

    fread(header, 1, 8, fp);

    if (png_sig_cmp((png_bytep)header, 0, 8)) {
        fprintf(stderr, "png_reader.c: file %s is not recognized as a PNG file\n", file_name);

        free(header);
        fclose(fp);

        return EXIT_FAILURE;
    }

    free(header);

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "png_reader.c: memory cannot be allocated for read struct\n");

        fclose(fp);

        return EXIT_FAILURE;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "png_reader.c: memory cannot be allocated for info struct\n");

        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);

        return EXIT_FAILURE;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        fprintf(stderr, "png_reader.c: memory cannot be allocated for end info struct\n");

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);

        return EXIT_FAILURE;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "png_reader.c: an error occurred during reading file %s\n", file_name);

        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);

        return EXIT_FAILURE;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, NUMBER_OF_CHECKED_BYTES);

    png_read_info(png_ptr, info_ptr);

    int width = (int)png_get_image_width(png_ptr, info_ptr);
    int height = (int)png_get_image_height(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "png_reader.c: an error occurred during reading file %s\n", file_name);

        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);

        return EXIT_FAILURE;
    }

    png_bytep bitmap[height];
    for (int y = 0; y < height; y++) {
        bitmap[y] = malloc(PIXEL_SIZE_DEFAULT * width * sizeof(uint8_t));
        if (!bitmap[y]) {
            fprintf(stderr, "png_reader.c: memory cannot be allocated for bitmap\n");

            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            /*TODO destroy_bitmap();*/
            fclose(fp);

            return EXIT_FAILURE;
        }
    }

    png_read_image(png_ptr, bitmap);

    png_read_end(png_ptr, end_info);

    make_grid(grid, width, height);

    if (write_bitmap_to_grid(grid, bitmap)) {
        fprintf(stderr, "png_reader.c: unknown pixel's color\n");

        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        /*TODO destroy_bitmap();*/
        fclose(fp);

        return EXIT_FAILURE;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    /*TODO destroy_bitmap();*/

    fclose(fp);

    return EXIT_SUCCESS;
}
