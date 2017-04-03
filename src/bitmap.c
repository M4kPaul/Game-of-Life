#include "bitmap.h"

void DestroyBitmap(bitmap_t *bitmap) {
    int y;

    for(y = 0; y < bitmap->height; y++) {
        free(bitmap->data[y]);
    }
}

int IsBlack(bitmap_t *bitmap, int x, int y) {
    if (bitmap->data[y][x] == 0 && bitmap->data[y][++x] == 0 && bitmap->data[y][++x] == 0) {
        return 1;
    }
    return 0;
}

int IsWhite(bitmap_t *bitmap, int x, int y) {
    if (bitmap->data[y][x] == 255 && bitmap->data[y][++x] == 255 && bitmap->data[y][++x] == 255) {
        return 1;
    }
    return 0;
}

int MakeBitmap(bitmap_t *bitmap, int width, int height) {
    int y;

    bitmap->width = width * PIXEL_SIZE_DEFAULT;
    bitmap->height = height;

    bitmap->data = calloc(bitmap->height * sizeof(png_bytep), sizeof(png_bytep));
    if(!bitmap->data) {
        fprintf(stderr, "bitmap.c: memory cannot be allocated for the bitmap\n");
    }

    for(y = 0; y < bitmap->height; y++) {
        bitmap->data[y] = calloc(PIXEL_SIZE_DEFAULT * bitmap->width * sizeof(png_byte), sizeof(png_byte));
        if(!bitmap->data[y]) {
            fprintf(stderr, "bitmap.c: memory cannot be allocated for the bitmap\n");

            free(bitmap->data);

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}