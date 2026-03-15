#ifndef MATRIX_H
#define MATRIX_H

#include "spi.h"
#include "ws2812b.h"
#include <stdint.h>

#define WIDTH 32
#define HEIGHT 8
#define NUM_LEDS (WIDTH * HEIGHT)
#define TX_LEN (NUM_LEDS * 9 + 90)

typedef struct {
  uint8_t r, g, b;
} pixel_t;

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

void render();

#endif
