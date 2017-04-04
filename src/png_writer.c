#include "png_writer.h"

static void ConvertGridToBitmap(grid_t *grid, bitmap_t *bitmap) {
    int y, x, i;

    for (y = 1; y <= grid->height; y++) {
        for (x = 1; x <= grid->width; x++) {
            i = PIXEL_SIZE_DEFAULT * (x - 1);

            if (grid->data[y][x] == 0) {
                bitmap->data[y - 1][i] = 255;
                bitmap->data[y - 1][++i] = 255;
                bitmap->data[y - 1][++i] = 255;
            } else {
                bitmap->data[y - 1][i] = 0;
                bitmap->data[y - 1][++i] = 0;
                bitmap->data[y - 1][++i] = 0;
            }
        }
    }
}

int WriteGridToPng(char *fileName, grid_t *grid) {
    FILE *fp = fopen(fileName, "wb");
    if (!fp) {
        fprintf(stderr, "png_writer.c: file %s cannot be opened for writing\n", fileName);

        return EXIT_FAILURE;
    }

    png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) {
        fprintf(stderr, "png_writer.c: memory cannot be allocated for write struct\n");

        fclose(fp);

        return EXIT_FAILURE;
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        png_destroy_write_struct(&pngPtr, NULL);
        fclose(fp);

        fprintf(stderr, "png_writer.c: memory cannot be allocated for info struct\n");

        return EXIT_FAILURE;
    }

    if (setjmp(png_jmpbuf(pngPtr))) {
        png_destroy_write_struct(&pngPtr, &infoPtr);
        fclose(fp);

        fprintf(stderr, "png_writer.c: an error occurred during writing file %s\n", fileName);

        return EXIT_FAILURE;
    }

    bitmap_t bitmap;

    if(MakeBitmap(&bitmap, grid->width, grid->height) == EXIT_FAILURE) {
        png_destroy_write_struct(&pngPtr, &infoPtr);
        fclose(fp);

        return EXIT_FAILURE;
    }

    ConvertGridToBitmap(grid, &bitmap);

    png_init_io(pngPtr, fp);

    png_set_IHDR(pngPtr, infoPtr, (png_uint_32)grid->width,
                 (png_uint_32)grid->height, PNG_DEPTH_DEFAULT,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(pngPtr, infoPtr);

    png_write_image(pngPtr, bitmap.data);

    png_write_end(pngPtr, NULL);

    DestroyBitmap(&bitmap);
    png_destroy_write_struct(&pngPtr, &infoPtr);
    fclose(fp);

    return EXIT_SUCCESS;
}
