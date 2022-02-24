
#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

#include "primitives.h"
#include "memory.h"
#include "cpu/cpu.h"
#include "ppu.h"

namespace gameboy {

class Console {
 public:
  Memory mem;
  PPU ppu;
  CPU cpu;

  Console();

  void initialize_registers();

  void run_a_instruction_cycle();

  void load_rom(Byte* rom);
};

}

#endif  // GAME_CONSOLE_H_