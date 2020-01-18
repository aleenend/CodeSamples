/*  Aleene Dupuy

    This header file contains structures for the
    header and pixel data, as well as various function prototypes.
*/

#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//structure for header data
typedef struct {
  char fileType[2];
  int cols, rows, num;
} header_t;
//structure for pixel data
typedef struct {
  unsigned char r, g, b;
} pixel_t;

//function prototypes
void readHeader(FILE *inFile, header_t *hData);
pixel_t** readPixel(FILE *inFile, header_t hData);
void writeHeader(FILE *outFile, header_t hData);
void writePixels(FILE *outFile, pixel_t **pixelArr, header_t hData);
void removeDigit(pixel_t **pixelArr, header_t hData);
void encodeMsg(FILE *outFile, header_t hData, pixel_t **pixelArr, char *msg);
void dec2bin(int* bin, int num);
void printByte(int* byte);

#endif
