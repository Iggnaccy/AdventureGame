CC := gcc
CFLAGS := -std=gnu11 $(shell pkg-config --cflags sdl SDL_ttf SDL_image)
LDLIBS := $(shell pkg-config --libs sdl SDL_ttf SDL_image)
TARGET := game

SRCS := $(wildcard src/*.c src/*.h)
OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(TARGET) obj/*.o

.PHONY: all clean
