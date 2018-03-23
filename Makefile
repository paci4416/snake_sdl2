CC = g++
OBJS = main.cpp game.cpp texture.cpp sprite.cpp snake.cpp font.cpp
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CFLAGS = -std=c++11
OUT = play

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(OUT)


.PHONY: clean

clean:
	rm play
