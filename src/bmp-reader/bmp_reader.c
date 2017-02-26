#include "bmp_reader.h"

char *ReadBMP(FILE *fn) {
  int sum;                /* suma RGB/3 = 0 || 1  */
  int i, j, k;            /* zmienne do pętli     */
  int row_padded;         /* przesunięcie         */
  char *in, *fixed;       /* BMP jako 0 i 1       */
  int height, width;      /* szereokość, wysokość */
  unsigned char *line;    /* linia z RGB pixela   */
  unsigned char info[54]; /* nagłówek BMP         */

  fread(info, sizeof(unsigned char), 54, fn);

  width = *(int*)&info[18];
  height = *(int*)&info[22];

  in = (char *)malloc(sizeof *in * width * height + 1);
                                     /* wielokrotność 4, nie do końca wiem czemu to działa BMP tworzy 4n bitów w rzędzie, */
  row_padded = (width*3 + 3) & (~3); /* a korzysta tylko się z tylu ile ma w szerekości ¯\_(ツ)_/¯                         */
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
      }
      else {
        in[i * width + j / 3] = '0';
      }
    }
  }
  
  i = height * width;
  fixed = (char *)malloc(sizeof *fixed * i + 1); /* normalnie bmp jest od lewego dolnego rogu */
  fixed[i] = '\0';
  for(j = 0, k = 0; j < width  * height; j++) {
    fixed[j] = in[i - width + k++];
    if (k % width == 0) {
      i -= width;
      k = 0;
    }
  }
  /*
  for(i = 0; i <= width * height; i++) {
    printf("%c", fixed[i]);
    if ((i + 1) % 38 == 0) printf("\n");
  }
  */

  return fixed;
}
