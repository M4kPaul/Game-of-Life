#ifndef GAME_OF_LIFE_BITMAP_H
#define GAME_OF_LIFE_BITMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <png.h>

#define PIXEL_SIZE_DEFAULT 3

typedef struct {
    int width;
    int height;
    png_bytepp data;
} bitmap_t;

void DestroyBitmap(bitmap_t *bitmap);

int IsBlack(bitmap_t *bitmap, int x, int y);

int IsWhite(bitmap_t *bitmap, int x, int y);

int MakeBitmap(bitmap_t *bitmap, int width, int height);

#endif /* BITMAP_H_ */
