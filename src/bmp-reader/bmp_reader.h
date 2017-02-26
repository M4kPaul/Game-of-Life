#ifndef BMP_READER_H_
#define BMP_READER_H_

#include <stdio.h>
#include <stdlib.h>

/* odczytuje bitmapę  */
/* zwraca ciąg 0, 1   */
/* 1 - komórka żywa   */
/* 0 - komórka martwa */

char *ReadBMP(FILE *fn);

#endif /* BMP_READER_H_ */
