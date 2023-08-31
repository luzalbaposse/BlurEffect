/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libbmp.h"
#include "lib/utils.h"

void loadImageAndParams(int argc, char **argv, char** inputFile, char** outputFile, BMP** image, int* value) {

  char* inputFileName;
  char* outputFileName;

  if(argc < 4) {
    printf("Usage:\n");
    printf("$ ./tp2 <inputFile> <outputFile> <count>\n\n");
    printf("Example:\n");
    printf("$ ./tp2 imagen.bmp resultado.bmp\n");
    exit(1);
  }

  *inputFile = argv[1];
  *outputFile = argv[2];
  *image = bmp_read(*inputFile);
  *value = atoi(argv[3]);

  uint32_t width = bmp_width(*image);
  uint32_t height = bmp_height(*image);
  uint32_t bytes = bmp_bytes_per_row(*image);
  uint16_t bits = bmp_bit_count(*image);
  uint32_t compress = bmp_compression(*image);
  
  printf("ancho: %i pixeles\n",width);
  printf("alto:  %i pixeles\n",height);
  printf("ancho en bytes: %i bytes\n",bytes);
  printf("bits por pixel: %i bits\n",bits);
  printf("compress codel: %i\n",compress);

  if(compress != 3 || bits != 32) {
    printf("Error: Tipo de imagen no soportado");
    exit(1);
  }
}

void step_blur3(int width, int height, uint8_t* data, uint8_t* res, int wFrom, int wTo, int hFrom, int hTo) {
  bgra_t (*image)[width] = (bgra_t (*)[width]) data;
  bgra_t (*result)[width] = (bgra_t (*)[width]) res;
  for(int i=hFrom; i<=hTo; i++) {
    for(int j=wFrom; j<=wTo; j++) {
          result[i][j].r = ( 1 * image[i-1][j-1].r + 2 * image[i-1][j+0].r + 1 * image[i-1][j+1].r +
                             2 * image[i+0][j-1].r + 4 * image[i+0][j+0].r + 2 * image[i+0][j+1].r +
                             1 * image[i+1][j-1].r + 2 * image[i+1][j+0].r + 1 * image[i+1][j+1].r ) / 16 ;
          result[i][j].g = ( 1 * image[i-1][j-1].g + 2 * image[i-1][j+0].g + 1 * image[i-1][j+1].g +
                             2 * image[i+0][j-1].g + 4 * image[i+0][j+0].g + 2 * image[i+0][j+1].g +
                             1 * image[i+1][j-1].g + 2 * image[i+1][j+0].g + 1 * image[i+1][j+1].g ) / 16 ;
          result[i][j].b = ( 1 * image[i-1][j-1].b + 2 * image[i-1][j+0].b + 1 * image[i-1][j+1].b +
                             2 * image[i+0][j-1].b + 4 * image[i+0][j+0].b + 2 * image[i+0][j+1].b +
                             1 * image[i+1][j-1].b + 2 * image[i+1][j+0].b + 1 * image[i+1][j+1].b ) / 16 ;
          result[i][j].a = 255;
    }
  }
}

void step_copy(int width, int height, uint8_t* data, uint8_t* res, int wFrom, int wTo, int hFrom, int hTo) {
  bgra_t (*image)[width] = (bgra_t (*)[width]) data;
  bgra_t (*result)[width] = (bgra_t (*)[width]) res;
  for(int i=hFrom; i<=hTo; i++) {
    for(int j=wFrom; j<=wTo; j++) {
          result[i][j].r = image[i][j].r;
          result[i][j].g = image[i][j].g;
          result[i][j].b = image[i][j].b;
          result[i][j].a = image[i][j].a;
    }
  }
}

void paintEdges(int width, int height, uint8_t* data) {
  bgra_t (*result)[width] = (bgra_t (*)[width]) data;
  for(int i=0; i<height; i++) {
    result[i][0].r = 0;
    result[i][0].g = 0;
    result[i][0].b = 0;
    result[i][0].a = 255;
    result[i][width-1].r = 0;
    result[i][width-1].g = 0;
    result[i][width-1].b = 0;
    result[i][width-1].a = 255;
  }
  for(int j=1; j<width-1; j++) {
    result[0][j].r = 0;
    result[0][j].g = 0;
    result[0][j].b = 0;
    result[0][j].a = 255;
    result[height-1][j].r = 0;
    result[height-1][j].g = 0;
    result[height-1][j].b = 0;
    result[height-1][j].a = 255;
  }
}

void setResultAndSaveImage(BMP *image, uint8_t* result, char* outputFile) {
  bmp_set_data(image, result);
  bmp_save(outputFile, image);
  bmp_delete(image);
}
