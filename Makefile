CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc
SRCS = src/main.c src/spi.c src/ws2812b.c src/matrix.c src/controllers/trail.c
OBJS = $(patsubst src/%.c, bin/%.o, $(SRCS))
TARGET = bin/matrix

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

bin/%.o: src/%.c | bin bin/controllers
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

bin/controllers:
	mkdir -p bin/controllers

clean:
	rm -rf bin
