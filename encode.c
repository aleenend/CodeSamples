/*  Aleene Dupuy
    
	 This file contains the implementations of functions in encode.h.
*/

#include "encode.h"

/*  
    This function gets the colums, rows, and color data from the image's header
    and saves the data in the structure for the header data. It does not return
    anything.
*/
void readHeader(FILE *inFile, header_t *hData) {

  //variable
  char buffer [256];

  //gets first line of image
  fgets(buffer, 256, inFile);

  //if first line is only file type
  if (strlen(buffer) == 3) {
    sscanf(buffer, "%s", hData->fileType);
    //gets second line of image
    fgets(buffer, 256, inFile);
    //if second line is only columns and rows
    if (strlen(buffer) < 9){
      sscanf(buffer, "%i %i", &hData->cols, &hData->rows);
      //gets third line of image
      fgets(buffer, 256, inFile);
      sscanf(buffer, "%i", &hData->num);
    }
    //second line contains the last three values
    else {
      sscanf(buffer, "%i %i %i", &hData->cols, &hData->rows, &hData->num);
    }
  }
  //if first line is only file type, columns, and rows
  else if (strlen(buffer) < 12) {
    sscanf(buffer, "%s %i %i", hData->fileType, &hData->cols, &hData->rows);
    //gets second line of image
    fgets(buffer, 256, inFile);
    sscanf(buffer, "%i", &hData->num);
  }
  //first line contains all necessary data
  else {
    sscanf(buffer, "%s %i %i %i", hData->fileType, &hData->cols, &hData->rows, &hData->num);
  }
}

/*  
    This function gets the pixel data from the image and saves the data in the
    structure for the pixel data.
*/
pixel_t** readPixel(FILE *inFile, header_t hData) {

  //variables
  int i = 0;
  int j = 0;

  //allocates data for pixel array using columns and rows
  pixel_t **pixelArr = (pixel_t **)malloc(hData.rows * sizeof(pixel_t *));
  for (i = 0; i < hData.rows; i++) {
    pixelArr[i] = (pixel_t *)malloc(hData.cols * sizeof(pixel_t));
  }
  //saves pixel data in pixel array
  for (i = 0; i < hData.rows; i++) {
    for (j = 0; j < hData.cols; j++) {
      pixelArr[i][j].r = fgetc(inFile);
      pixelArr[i][j].g = fgetc(inFile);
      pixelArr[i][j].b = fgetc(inFile);
    }
  }

  return pixelArr;

}

/*  
    This function writes the header info in the image file using the width and
    height gotten from the image file input by user. It does not return
    anything.
*/
void writeHeader(FILE* outFile, header_t hData) {

  fprintf(outFile, "%s\n%d %d %d\n", hData.fileType, hData.cols, hData.rows,
    hData.num);
}

/*  
    This function writes the image in the image file using the pixel data from
    the image file input by user. It does not return anything.
*/
void writePixels(FILE* outFile, pixel_t **pixelArr, header_t hData) {

  //variables
  int i = 0;
  int j = 0;

  //prints pixel data to output file
  for (i = 0; i < hData.rows; i++) {
    for (j = 0; j < hData.cols; j++) {
      fprintf(outFile, "%c%c%c", pixelArr[i][j].r, pixelArr[i][j].g,
        pixelArr[i][j].b);
    }
  }
}

/*  
    This function changes the last digit of each value in the pixel array to
    0 so the message can be encoded. It does not return anything.
*/
void removeDigit(pixel_t **pixelArr, header_t hData) {

  //variables
  int i = 0;
  int j = 0;

  for (i = 0; i < hData.rows; i++) {
    for (j = 0; j < hData.cols; j++) {
      pixelArr[i][j].r = pixelArr[i][j].r - (pixelArr[i][j].r % 10);
      pixelArr[i][j].g = pixelArr[i][j].g - (pixelArr[i][j].g % 10);
      pixelArr[i][j].b = pixelArr[i][j].b - (pixelArr[i][j].b % 10);
    }
  }
}

/*  
    This function  writes the header to the output file and then converts
    the message to be encoded into binary and encodes it into the image pixel
    by pixel. It then writes the image to the output file. It does not return
    anything.
*/
void encodeMsg(FILE *outFile, header_t hData, pixel_t **pixelArr, char *msg) {

  //variables
  int cCount = 0;
  int bitCount = 0;
  int array[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  int j = 0;
  int k = 0;

  //writes header data to output file
  writeHeader(outFile, hData);

    //loops throuh rows and colums to convert message and encode it in image
    for (i = 0; i < hData.rows; i++) {
      for (j = 0; j < hData.cols; j++) {
        //if no bits have been encoded, get bits
        if (bitCount == 0) {
          //call to dec2bin to get first set of bits
          dec2bin(array, msg[k]);
          pixelArr[i][j].r += array[bitCount];
          bitCount++;
          pixelArr[i][j].g += array[bitCount];
          bitCount++;
          pixelArr[i][j].b += array[bitCount];
          bitCount++;
        }
        //if all 9 bits have been encoded, get next set of bits
        else if (bitCount == 9) {
          //call to dec2bin to get next set of bits
          dec2bin(array, msg[++k]);
          //resets bitCount
          bitCount = 0;
          cCount++;
          pixelArr[i][j].r += array[bitCount];
          bitCount++;
          pixelArr[i][j].g += array[bitCount];
          bitCount++;
          pixelArr[i][j].b += array[bitCount];
          bitCount++;
        }
        //if amount of characters printed is equal to length of message
        else if (cCount == strlen(msg)) {
          break;
        }
        else {
          pixelArr[i][j].r += array[bitCount];
          bitCount++;
          pixelArr[i][j].g += array[bitCount];
          bitCount++;
          pixelArr[i][j].b += array[bitCount];
          bitCount++;
        }
      }
    }
  //writes pixels to output file
  writePixels(outFile, pixelArr, hData);
}
/*  
    This function takes the decimal value of a character and converts it to
    binary. It does not return anything.
*/
void dec2bin(int* bin, int num) {

  //variable
  int i = 8;

  //converts number to binary and saves in bin backwards
  while (i > 0) {
    bin[i] = (num % 2);
    num = num / 2;
    i--;
  }
  //saves final binary digit
  bin[i] = num;

}

/*  
    This function prints out the binary value equal to the decimal value of
    a character from the message. It is for debugging purposes only and does
    not return anything.
*/
void printByte(int* byte) {

  //variable
  int i = 0;

  //prints out binary value in array
  for (i = 0; i < 9; i++) {
    fprintf(stdout, "%d", byte[i]);
  }
  fprintf(stdout, "\n");
}
