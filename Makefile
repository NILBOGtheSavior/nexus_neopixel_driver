CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc
SRCS = src/main.c src/spi.c src/ws2812b.c src/matrix.c
OBJS = $(SRCS:src/%.c=bin/%.o)
TARGET = bin/matrix

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

bin/%.o: src/%.c | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

clean:
	rm -rf bin
