#include "controllers/controller.h"
#include "controllers/trail.h"
#include "matrix.h"
#include "spi.h"

int main() {
  initialize_spi();

  controller_t *active = get_default_controller();
  active->init();

  while (1) {
    active->update();
    render();
    usleep(16000); // ~60fps
  }
}
