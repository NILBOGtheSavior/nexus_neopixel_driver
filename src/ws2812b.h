#ifndef WS2812B_H
#define WS2812B_H

#include <stdint.h>

void encode_byte(uint8_t in, uint8_t *out);

void encode_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t *out);

#endif
