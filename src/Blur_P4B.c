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

typedef struct {
// esto es para crear alias o nombres alternativos para tipos de datos que ya declaramos, habría que preguntar si lo podemos usar. es para mejorar la lectura del codigo no + (att: Lu)
  int start_col;
  int end_col;
  int start_row;
  int end_row;
} ThreadArgs;

static void* processBox(void* arg) {
  ThreadArgs* args = (ThreadArgs*)arg;
  int start_col = args->start_col;
  int end_col = args->end_col;
  int start_row = args->start_row;
  int end_row = args->end_row;

  step_blur3(width, height, data, result, start_col, end_col, start_row, end_row);
  pthread_exit(NULL);
}

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
  // Dividir el trabajo en cuadrados entre cuatro threads
  int col_mid = width / 2;
  int row_mid = height / 2;

  pthread_t threads[4];
  ThreadArgs args[4];

  for (int i = 0; i < 4; i++) {
    args[i].start_col = (i % 2) * col_mid;
    args[i].end_col = ((i % 2) + 1) * col_mid - 1;
    args[i].start_row = (i / 2) * row_mid;
    args[i].end_row = ((i / 2) + 1) * row_mid - 1;
    pthread_create(&threads[i], NULL, processBox, &args[i]);
  }

  // Esperar a que todos los threads terminen
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  // Liberacion de memoria
  free(data);

  // Guardado de la imagen
  setResultAndSaveImage(img, result, outputFileName);

  return 0;
}
