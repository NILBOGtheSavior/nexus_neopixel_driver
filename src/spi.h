#ifndef SPI_H
#define SPI_H

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void initialize_spi();
void write_spi(uint8_t *buffer, int len);

#endif
