#include "ws2812b.h"

void encode_byte(uint8_t in, uint8_t *out) {
  uint32_t res = 0;
  for (int i = 7; i >= 0; --i) {
    res <<= 3;
    if (in & (1 << i))
      res = res | 0b110;
    else
      res = res | 0b100;
  }
  out[0] = (res >> 16) & 0xFF;
  out[1] = (res >> 8) & 0xFF;
  out[2] = (res) & 0xFF;
}

void encode_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t *out) {
  encode_byte(g, out);
  encode_byte(r, out + 3);
  encode_byte(b, out + 6);
}
