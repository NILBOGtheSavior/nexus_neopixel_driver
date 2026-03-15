#include "spi.h"

static const char *device = "/dev/spidev0.0";
static uint32_t mode = SPI_MODE_0;
static uint8_t bits = 0;
static uint32_t speed = 2400000;
static int spi_connection = -1;

void initialize_spi() {
  spi_connection = open(device, O_RDWR);
  if (spi_connection < 0) {
    printf("can't open device");
    exit(1);
  }

  ioctl(spi_connection, SPI_IOC_WR_MODE32, &mode);
  ioctl(spi_connection, SPI_IOC_RD_MODE32, &mode);
  ioctl(spi_connection, SPI_IOC_WR_BITS_PER_WORD, &bits);
  ioctl(spi_connection, SPI_IOC_RD_BITS_PER_WORD, &bits);
  ioctl(spi_connection, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  ioctl(spi_connection, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
}

void write_spi(uint8_t *buffer, int len) { write(spi_connection, buffer, len); }
