#include "bmp_reader.h"

int ReadBMP(char *fileName, grid_t *grid) {
    int sum;                 /* suma RGB/3 = 0 || 1        */
    int i, j, k;             /* zmienne do pętli           */
    size_t rowPadded;        /* przesunięcie               */
    unsigned char *in;       /* BMP jako 0 i 1             */
    unsigned char *line;     /* linia z RGB pixela         */
    unsigned char info[54];  /* nagłówek BMP               */
    int height, width, area; /* szereokość, wysokość, pole */

    FILE *fp;

    fp = fopen(fileName, "rb");
    if (!fp) {
        fprintf(stderr, "bmp_reader.c: file %s cannot be open for reading\n", fileName);
        return EXIT_FAILURE;
    }

    fread(info, sizeof(unsigned char), 54, fp);

    width = *(int *)&info[18];
    height = *(int *)&info[22];

    in = (unsigned char *)malloc(sizeof *in * width * height + 1);

    rowPadded = (size_t)((width * 3 + 3) & (~3));
    line = (unsigned char *)malloc(sizeof *line * rowPadded + 1);
    for (i = 0; i < height; i++) {
        fread(line, sizeof(unsigned char), rowPadded, fp);
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
    fclose(fp);

    MakeGrid(grid, width, height);

    area = height * width;
    for (i = 1; i <= height; i++) {
        for (j = 0; j < width; j++) {
            grid->data[i + 1][j + 1] = in[area - i * width + j] - '0';
        }
    }

    free(in);

    return EXIT_SUCCESS;
}
