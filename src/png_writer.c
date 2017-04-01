#include "png_writer.h"

static void convert_grid_to_bitmap(grid_t *grid, png_bytepp bitmap) {
    int position;

    for (int y = 1; y <= grid->height; y++) {
        png_bytep row = malloc(PIXEL_SIZE_DEFAULT * grid->width * sizeof(uint8_t));
        for (int x = 1; x <= grid->width; x++) {
            position = PIXEL_SIZE_DEFAULT * (x - 1);
            if (grid->data[y][x] == 0) {
                row[position] = 255;
                row[++position] = 255;
                row[++position] = 255;
            } else {
                row[position] = 0;
                row[++position] = 0;
                row[++position] = 0;
            }
        }
        bitmap[y - 1] = row;
    }
}

int write_grid_to_png(grid_t *grid, char *file_name) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        fprintf(stderr, "png_writer.c: file %s cannot be opened for writing\n", file_name);

        return EXIT_FAILURE;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "png_writer.c: memory cannot be allocated for write struct\n");

        fclose(fp);

        return EXIT_FAILURE;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);

        fprintf(stderr, "png_writer.c: memory cannot be allocated for info struct\n");

        return EXIT_FAILURE;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);

        fprintf(stderr, "png_writer.c: an error occurred during writing file %s\n", file_name);

        return EXIT_FAILURE;
    }

    png_bytep bitmap[grid->height];

    convert_grid_to_bitmap(grid, bitmap);

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, (png_uint_32)grid->width,
                 (png_uint_32)grid->height, PNG_DEPTH_DEFAULT,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    png_write_image(png_ptr, bitmap);

    png_write_end(png_ptr, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);

    return EXIT_SUCCESS;
}
