#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void initialize_spi();
void write_spi(uint8_t *buffer, int len);

#endif
