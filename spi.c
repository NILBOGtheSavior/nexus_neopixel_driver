#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static const char *device = "/dev/spidev0.0";
static uint32_t mode = SPI_MODE_0;
static uint8_t bits = 0;
static uint32_t speed = 2400000;

static uint8_t buff[2394];

int die(char *s) {
  printf("%s", s);
  exit(1);
}

void encode_byte(uint8_t in, uint8_t *out) {
  uint32_t res = 0;
  for (int i = 7; i >= 0; --i) {
    res <<= 3;
    if (in & (1 << i))
      res = res | 0b110;
    else
      res = res | 0b100;
  }
  out[0] = (res >> 16) & 0xFF;
  out[1] = (res >> 8) & 0xFF;
  out[2] = (res) & 0xFF;
}

void encode_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t *out) {
  encode_byte(g, out);
  encode_byte(r, out + 3);
  encode_byte(b, out + 6);
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Usage: ./test r g b\n");
    exit(1);
  }

  int f;
  f = open(device, O_RDWR);
  if (f < 0)
    die("can't open device");

  ioctl(f, SPI_IOC_WR_MODE32, &mode);
  ioctl(f, SPI_IOC_RD_MODE32, &mode);
  ioctl(f, SPI_IOC_WR_BITS_PER_WORD, &bits);
  ioctl(f, SPI_IOC_RD_BITS_PER_WORD, &bits);
  ioctl(f, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  ioctl(f, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

  memset(buff, 0, 2394);

  for (int i = 0; i <= 256; ++i)
    encode_pixel(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), buff + (9 * i));

  write(f, buff, 2394);

  return 0;
}
