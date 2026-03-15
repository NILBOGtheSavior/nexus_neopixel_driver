#include "trail.h"

#include "../matrix.h"
#include <stdint.h>

#define TRAIL_LENGTH 8
#define TRAIL_COLOR_R 0
#define TRAIL_COLOR_G 100
#define TRAIL_COLOR_B 255

static int head = 0;
static int done = 0;

static void trail_init() {
  head = 0;
  done = 0;
}

static void trail_update() {
  if (done)
    return;

  for (int i = 0; i < NUM_LEDS; i++) {
    int dist = head - i;
    if (dist == 0) {
      set_pixel(i % WIDTH, i / WIDTH, TRAIL_COLOR_R, TRAIL_COLOR_G,
                TRAIL_COLOR_B);
    } else if (dist > 0 && dist <= TRAIL_LENGTH) {
      uint8_t fade = 255 - (dist * (255 / TRAIL_LENGTH));
      set_pixel(i % WIDTH, i / WIDTH, (TRAIL_COLOR_R * fade) / 255,
                (TRAIL_COLOR_G * fade) / 255, (TRAIL_COLOR_B * fade) / 255);
    } else {
      set_pixel(i % WIDTH, i / WIDTH, 0, 0, 0);
    }
  }

  head++;
  if (head >= NUM_LEDS + TRAIL_LENGTH + 1)
    done = 1;
}

static controller_t trail_controller = {.init = trail_init,
                                        .update = trail_update};

controller_t *get_default_controller() { return &trail_controller; }
