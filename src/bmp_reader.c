#include "bmp_reader.h"

int ReadBMP(FILE *fn, grid_t *grid) {
    int sum;                 /* suma RGB/3 = 0 || 1        */
    int i, j, k;             /* zmienne do pętli           */
    size_t row_padded;       /* przesunięcie               */
    unsigned char *in;       /* BMP jako 0 i 1             */
    unsigned char *line;     /* linia z RGB pixela         */
    unsigned char info[54];  /* nagłówek BMP               */
    int height, width, area; /* szereokość, wysokość, pole */

    fread(info, sizeof(unsigned char), 54, fn);

    width = *(int *)&info[18];
    height = *(int *)&info[22];

    in = (unsigned char *)malloc(sizeof *in * width * height + 1);

    row_padded = (size_t)((width * 3 + 3) & (~3));
    line = (unsigned char *)malloc(sizeof *line * row_padded + 1);
    for (i = 0; i < height; i++) {
        fread(line, sizeof(unsigned char), row_padded, fn);
        for (j = 0; j < width * 3; j += 3) {
            sum = 0;
            for (k = 0; k < 3; k++) {
                sum += line[j + k];
            }
            if (sum / 3.0 < 0.5 * 255) {
                in[i * width + j / 3] = '1';
            } else {
                in[i * width + j / 3] = '0';
            }
        }
    }

    free(line);

    make_grid(grid, width, height);

    area = height * width;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            grid->data[i + 1][j + 1] = in[area - width + j] - '0';
        }
    }

    free(in);

    return EXIT_SUCCESS;
}
