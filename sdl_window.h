#ifndef _SDL_WINDOW_H_
#define _SDL_WINDOW_H_

#include "libs.h"

#include "SDL.h"

#include "chip8.h"

// For SDL, SDL Window
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl_t;

// Intialize SDL with its subsystems
bool init_sdl(sdl_t *sdl, const config_t config);

// Cleanup
void final_cleanup(const sdl_t sdl);

// Clear screen / SDL window to bg color
void clear_screen(const sdl_t sdl, const config_t config); 

// Update window with any changes
void update_screen(const sdl_t sdl);

// Handle user input
void handle_input(chip8_t *chip8);

#endif
