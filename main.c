#include "sdl_window.h"
#include "chip8.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    // Initialize emulator/config options
    config_t config = {0};
    if (!set_config_from_args(&config, argc, argv)) exit(EXIT_FAILURE);

    // Initialize SDL
    sdl_t sdl = {0}; 
    if (!init_sdl(&sdl, config)) exit(EXIT_FAILURE);
    
    chip8_t chip8 = {0};
    const char *rom_name = argv[1];
    if (!init_chip8(&chip8, rom_name)) exit(EXIT_FAILURE);

    // Initial screen clear to background color
    clear_screen(sdl, config);

    // Main emulator loop
    while (chip8.state != QUIT) {
        // Handle user input
        handle_input(&chip8);

        if (chip8.state == PAUSED) continue;

        // Emulate CHIP8 instructions
        // Get_time() elapsed since last get_time();
        
        // Delay for approx. 60hz/60fps (16.67ms)
        SDL_Delay(16);
       
        // Update window with changes
        update_screen(sdl);
    }

    // Final cleanup
    final_cleanup(sdl);

    exit(EXIT_SUCCESS);
}
