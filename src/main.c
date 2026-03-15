#include "matrix.h"
#include "spi.h"
#include "ws2812b.h"

void color_wheel(uint8_t pos, uint8_t *r, uint8_t *g, uint8_t *b) {
  if (pos < 85) {
    *r = pos * 3;
    *g = 255 - pos * 3;
    *b = 0;
  } else if (pos < 170) {
    pos -= 85;
    *r = 255 - pos * 3;
    *g = 0;
    *b = pos * 3;
  } else {
    pos -= 170;
    *r = 0;
    *g = pos * 3;
    *b = 255 - pos * 3;
  }
}

int main() {
  initialize_spi();
  int offset = 0;
  while (1) {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        uint8_t pos = (x + y * 2 + offset);
        uint8_t r;
        uint8_t g;
        uint8_t b;
        color_wheel(pos, &r, &g, &b);
        set_pixel(x, y, r, g, b);
      }
    }
    offset++;
    render();
    usleep(16000); // ~60fps
  }
}
