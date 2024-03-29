CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -Wno-unused-command-line-argument
SDL_FLAGS = -I/opt/homebrew/Cellar/sdl2/2.28.5/include -L/opt/homebrew/Cellar/sdl2/2.28.5/lib -lSDL2

all: main

main: main.c
	$(CC) $(CFLAGS) $(SDL_FLAGS) -o main main.c
