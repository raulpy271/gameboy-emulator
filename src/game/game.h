
#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

#include "primitives.h"
#include "memory.h"
#include "cpu/cpu.h"
#include "ppu.h"
#include "timer_registers.h"
#include "keypad.h"

namespace gameboy {

class Console {
 public:
  Memory mem;
  PPU ppu;
  CPU cpu;
  TimerRegisters timer;

  Console();

  void initialize_registers();

  void run_a_instruction_cycle();

  void load_rom(Byte* rom);

  void HandleBottonEvent(Botton botton, BottonEventType type);

  void ScanLineAndSTATInterruptions();

  void RunAFrameAndExecuteInstructions();

};

}

#endif  // GAME_CONSOLE_H_