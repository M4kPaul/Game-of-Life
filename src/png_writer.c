#include "png_writer.h"

static void ConvertGridToBitmap(grid_t *grid, bitmap_t *bitmap) {
    int y, x, i;

    for (y = 1; y <= grid->height; y++) {
        for (x = 1; x <= grid->width; x++) {
            i = PIXEL_SIZE_DEFAULT * (x - 1);

            if (grid->data[y][x] == 0) {
                bitmap->data[y][i] = 255;
                bitmap->data[y][++i] = 255;
                bitmap->data[y][++i] = 255;
            } else {
                bitmap->data[y][i] = 0;
                bitmap->data[y][++i] = 0;
                bitmap->data[y][++i] = 0;
            }
        }
    }
}

int WriteGridToPng(grid_t *grid, char *file_name) {
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

    bitmap_t bitmap;

    if(MakeBitmap(&bitmap, grid->width, grid->height) == EXIT_FAILURE) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);

        return EXIT_FAILURE;
    }

    ConvertGridToBitmap(grid, &bitmap);

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, (png_uint_32)grid->width,
                 (png_uint_32)grid->height, PNG_DEPTH_DEFAULT,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    png_write_image(png_ptr, bitmap.data);

    png_write_end(png_ptr, NULL);

    DestroyBitmap(&bitmap);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return EXIT_SUCCESS;
}
