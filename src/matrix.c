#include "matrix.h"

static pixel_t framebuffer[NUM_LEDS];
static uint8_t buffer[TX_LEN];

int xy_to_index(int x, int y) {
    int index;
    if (x % 2) {
        index = x * HEIGHT + (HEIGHT - 1 - y);
    } else {
        index = x * HEIGHT + y;
    }
    return index;
}

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  framebuffer[xy_to_index(x, y)] = (pixel_t){r, g, b};
}

void render() {
  for (int i = 0; i < NUM_LEDS; ++i)
    encode_pixel(framebuffer[i].r, framebuffer[i].g, framebuffer[i].b,
                 buffer + (9 * i));
  write_spi(buffer, TX_LEN);
}
