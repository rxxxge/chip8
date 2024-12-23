CFLAGS=-std=c17 -Wall -Wextra -Werror
LIBS=.\SDL2-2.30.10\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2
INCLUDES=.\SDL2-2.30.10\x86_64-w64-mingw32\include\SDL2

all:
	gcc main.c sdl_window.c chip8.c -o main $(CFLAGS) -L$(LIBS) -I$(INCLUDES)	

linux:
	gcc main.c sdl_window.c chip8.c -o main $(CFLAGS) `sdl2-config --cflags --libs`
