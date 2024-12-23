#ifndef _CHIP8_T_
#define _CHIP8_T_

#include "libs.h"

// For emulator configuration
typedef struct {
    uint32_t window_width;   
    uint32_t window_height; 
    uint32_t fg_color;          // Foreground color RGBA8888
    uint32_t bg_color;          // Background color RGBA8888
    uint32_t scale_factor;      // Amount to scale a chip8 pixel by e.g. 20x (20x larger window)
} config_t;

// Emulator states
typedef enum {
    QUIT = 0,
    RUNNING,
    PAUSED
} emulator_state_t;

// Chip8 Instruction Format
typedef struct {
    uint16_t opcode;
    uint16_t NNN;   // 12 bit address/constant
    uint8_t NN;     // 8 bit constant
    uint8_t N;      // 4 bit constant
    uint8_t X;      // 4 bit register identifier
    uint8_t Y;      // 4 bit register identifier
} instruction_t;

// CHIP8 Machine object
typedef struct {
    emulator_state_t state;
    uint8_t ram[4096];
    bool display[64*32];    // Emulate original CHIP8 resolution pixels
    uint16_t stack[12];     // Subroutine stack
    uint8_t V[16];          // Data registers V0 - VF
    uint16_t I;
    uint16_t PC;            // Program counter
    uint8_t delay_timer;    // Decrements at 60hz when >0
    uint8_t sound_timer;    // Decrements at 60hz when >0 and plays tone
    bool keypad[16];        // Hexadecimal keypad 0x0 - 0xF
    const char *rom_name;   // Name of running rom (failed loaded)
    instruction_t inst;     // Currently executing instruction
} chip8_t;

// Set up initial emulator configuration from passed in arguments
bool set_config_from_args(config_t *config, const int argc, char **argv);

// Initialize CHIP8 machine
bool init_chip8(chip8_t *chip8, const char rom_name[]); 

#endif
