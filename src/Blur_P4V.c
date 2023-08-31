/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lib/libbmp.h"
#include "lib/utils.h"
#include "common.h"

uint32_t width;
uint32_t height;
uint8_t* data;
uint8_t* result;

int main(int argc, char **argv) {

  char* inputFileName;
  char* outputFileName;
  int count;
  BMP* img;

  // Cargado de imagen en memoria
  loadImageAndParams(argc, argv, &inputFileName, &outputFileName, &img, &count);
  width = bmp_width(img);
  height = bmp_height(img);
  data = bmp_data(img);

  // Solicito memoria para datos temporales
  result = (uint8_t*) malloc(width * height * sizeof(bgra_t));
  step_copy(width, height, data, result, 0, width-1, 0, height-1);
  
  // Procesamiento de la imagen
  // COMPLETAR

  // Liberacion de memoria
  free(data);

  // Guardado de la imagen
  setResultAndSaveImage(img, result, outputFileName);

  return 0;
}
