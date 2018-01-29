CC := gcc
CFLAGS := -std=gnu11
SDLFLAGS := $(shell echo `sdl-config --cflags --libs`)
TARGET := game

SRCS := $(wildcard src/*.c src/*.h)
OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SDLFLAGS) -o $@ $^

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) obj/*.o

.PHONY: all clean
