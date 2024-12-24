#include "chip8.h"
#include "sdl_window.h"

// Set up initial emulator configuration from passed in arguments
bool set_config_from_args(config_t *config, const int argc, char **argv) {
   // Set by default
   *config = (config_t) {
        .window_width = 64,
        .window_height = 32,
        .fg_color = 0xFFFFFFFF,     // RGBA
        .bg_color = 0x000000FF,
        .scale_factor = 20,         // 1280x640
   };

   // Override defaults from passed arguments
   for (int i = 0; i < argc; i++) {
       (void)argv[i];   // Prevent unused variables
   }

   return true;
}

// Initialize CHIP8 machine
bool init_chip8(chip8_t *chip8, const char rom_name[]) {
    const uint32_t entry_point = 0x200; // Chip8 ROMs are loaded to 0x200
    const uint8_t font[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    // Load font
    memcpy(&chip8->ram[0], font, sizeof(font));      

    // Load ROM
    FILE *rom = fopen(rom_name, "rb");
    if (!rom) {
        SDL_Log("Rom file %s is invalid or doesn't exist!\n", rom_name);
        return false;
    }
    
    // Get/check rom size
    fseek(rom, 0, SEEK_END);
    const size_t rom_size = ftell(rom);
    const size_t max_size = sizeof chip8->ram - entry_point; 
    rewind(rom);

    if (rom_size > max_size) {
        SDL_Log("Rom file %s is too big! Rom size: %"PRIuPTR" size allowed: %"PRIuPTR"\n", 
                rom_name, rom_size, max_size);
        return false;
    }

    if (fread(&chip8->ram[entry_point], rom_size, 1, rom) != 1) {
        SDL_Log("Could not read Rom file %s into CHIP8 memory\n",
                rom_name);
        return false;
    }

    fclose(rom);

    // Set chip8 machine defaults
    chip8->state = RUNNING;
    chip8->PC = entry_point;    // Start at 0x200
    chip8->rom_name = rom_name;

    return true;
}

// Emulate 1 CHIP8 instruction
void emulate_instruction(chip8_t *chip8) {
    // Get next opcode from ram
    chip8->inst.opcode = (chip8->ram[chip8->PC] << 8) | chip8->ram[chip8->PC + 1];
    chip8->PC += 2;   // Pre increment program counter for next opcode
    
    // Instruction format
    chip8->inst.NNN = chip8->inst.opcode & 0x0FFF;
    chip8->inst.NN  = chip8->inst.opcode & 0x0FF;
    chip8->inst.N   = chip8->inst.opcode & 0x0F;
    chip8->inst.X   = (chip8->inst.opcode >> 8) & 0x0F;
    chip8->inst.Y   = (chip8->inst.opcode >> 4) & 0x0F;   
   
    // Emulate opcode
    switch (chip8->inst.opcode) {
        case 0x0:
            if (chip8->inst.NN == 0xE0) {
                
                // 0x00E0: Clear the screen
                
            }
        default:
          break; // Unimplemented or invalid opcode
    }
}
