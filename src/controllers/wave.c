#include "wave.h"

static int offset = 0;

static void wave_init() { offset = 0; }

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

static void wave_update() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      uint8_t pos = x + y + offset;
      uint8_t r;
      uint8_t g;
      uint8_t b;
      color_wheel(pos, &r, &g, &b);
      set_pixel(x, y, r, g, b);
    }
  }
  ++offset;
}

static controller_t wave_controller = {.init = wave_init,
                                       .update = wave_update};

controller_t *get_wave_controller() { return &wave_controller; }
