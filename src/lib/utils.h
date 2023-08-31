/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SAT utils_saturate

typedef struct bgra_t {
    unsigned char b, g, r, a;
} __attribute__((packed)) bgra_t;

typedef struct bgra16_t {
    unsigned short b, g, r, a;
} __attribute__((packed)) bgra16_t;

typedef struct bgra32_t {
    unsigned int b, g, r, a;
} __attribute__((packed)) bgra32_t;

typedef struct bgr_t {
    unsigned char b, g, r;
} __attribute__((packed)) bgr_t;

typedef struct bgr16_t {
    unsigned short b, g, r;
} __attribute__((packed)) bgr16_t;

typedef struct bgr32_t {
    unsigned int b, g, r;
} __attribute__((packed)) bgr32_t;

uint8_t utils_saturate(int32_t a);


void utils_copyBorders32( uint8_t *src, uint8_t *dst,
                          int width, int height, int row_size,
                          int size);

void utils_paintBorders32( uint8_t *dst,
                           int width, int height, int row_size,
                           int size, uint32_t rgba);

void utils_paintBorders8( uint8_t *dst,
                          int width, int height, int row_size,
                          int size, uint8_t color);

uint8_t* utils_verticalFlip(uint8_t *src, int height, int width);

#endif /* !__UTILS__H__ */

