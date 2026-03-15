#include "controllers/controller.h"
#include "controllers/trail.h"
#include "controllers/wave.h"
#include "matrix.h"
#include "spi.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static controller_t *active;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *repl(void *arg) {
  char input[64];
  while (1) {
    printf("> ");
    fflush(stdout);
    fgets(input, sizeof(input), stdin);

    pthread_mutex_lock(&lock);
    if (input[0] == '1') {
      active = get_wave_controller();
      active->init();
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, repl, NULL);
  initialize_spi();

  active = get_default_controller();
  active->init();

  while (1) {
    pthread_mutex_lock(&lock);
    active->update();
    pthread_mutex_unlock(&lock);
    render();
    usleep(16000);
  }
}
