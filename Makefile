CFLAGS=-std=c17 -Wall -Wextra -Werror

# Windows specific
LIBS=.\SDL2-2.30.10\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2
INCLUDES=.\SDL2-2.30.10\x86_64-w64-mingw32\include\SDL2

BUILD_DIR=build
TARGET=$(BUILD_DIR)/main

# default target
all: linux

# build for windows (make windows)
windows: | $(BUILD_DIR)
	gcc main.c sdl_window.c chip8.c -o $(TARGET).exe $(CFLAGS) -L$(LIBS) -I$(INCLUDES)

# build for linux (run make linux)
linux: | $(BUILD_DIR)
	gcc main.c sdl_window.c chip8.c -o $(TARGET) $(CFLAGS) `sdl2-config --cflags --libs`

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
