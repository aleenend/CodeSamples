/*  Aleene Dupuy

    This is the main driver. It calls functions to read and
    save header and pixel data from an input file. It then calls a function
    to change the last digit of each pixel value to 0, and another function
    to encode a message into the pixel data, and write the image to an output
    file.
*/

#include "encode.h"

int main(int argc, char *argv[]) {

  //variables
  FILE *inputFile;
  FILE *outputFile;
  header_t headerData;
  pixel_t **pixelData;
  char *message = "Programming is cool!";

  //checks to make sure user entered correct amount of command line arguments
  if (argc < 3) {
    fprintf(stdout, "<executable> <input_file> <output_file>\n");
    exit(1);
  }
  //opens first file named in command line
  inputFile = fopen(argv[1], "r");

  //checks to make sure file opened correctly
  if (inputFile == NULL) {
    fprintf(stdout, "Error opening file. Exiting program.\n");
    exit(1);
  }

  //call to function to get the header data from input file
  readHeader(inputFile, &headerData);
  //call to function to get pixel data from input file
  pixelData = readPixel(inputFile, headerData);

  fclose(inputFile);

  //opens second file named in command line
  outputFile = fopen(argv[2], "w");

  //checks to make sure file opened correctly
  if (outputFile == NULL) {
    fprintf(stdout, "Error opening file. Exiting program.\n");
    exit(1);

  }
  //call to function to change last digits of pixel data to 0
  removeDigit(pixelData, headerData);
  //call to function to encode message in image
  encodeMsg(outputFile, headerData, pixelData, message);

  fclose(outputFile);
  
  //frees memory allocated for pixel array
  free(pixelData);

  return 0;
}
