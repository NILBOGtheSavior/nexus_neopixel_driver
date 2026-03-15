#include "clock.h"

static const uint8_t font[10][8] = {
    {0x00, 0x39, 0x46, 0x4A, 0x52, 0x62, 0x39, 0x00}, // 0
    {},                                               // 1
    {},                                               // 2
    {},                                               // 3
    {},                                               // 4
    {},                                               // 5
    {},                                               // 6
    {},                                               // 7
    {},                                               // 8
    {}                                                // 9
};

static void draw_digit(int digit, int start_x, uint8_t r, uint8_t g,
                       uint8_t b) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 6; col++) {
      if (font[digit][row] & (1 << (5 - col))) {
        set_pixel(start_x + col, row, r, g, b);
      } else {
        set_pixel(start_x + col, row, 0, 0, 0);
      }
    }
  }
}

static void clock_init() {}

static void clock_update() {
  draw_digit(0, 0, 255, 255, 255);
  draw_digit(0, 7, 255, 255, 255);
  draw_digit(0, 17, 255, 255, 255);
  draw_digit(0, 24, 255, 255, 255);
}

static controller_t clock_controller = {.init = clock_init,
                                        .update = clock_update};

controller_t *get_clock_controller() { return &clock_controller; }
