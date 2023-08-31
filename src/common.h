/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libbmp.h"
#include "lib/utils.h"

void loadImageAndParams(int argc, char **argv, char** inputFile, char** outputFile, BMP** image, int* value);

void step_blur3(int width, int height, uint8_t* data, uint8_t* res, int wFrom, int wTo, int hFrom, int hTo);

void step_copy(int width, int height, uint8_t* data, uint8_t* res, int wFrom, int wTo, int hFrom, int hTo);

void paintEdges(int width, int height, uint8_t* data);

void setResultAndSaveImage(BMP *image, uint8_t* result, char* outputFile);
