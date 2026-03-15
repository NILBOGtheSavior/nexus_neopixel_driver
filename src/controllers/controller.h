#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct {
  void (*init)();
  void (*update)();
} controller_t;

#endif
