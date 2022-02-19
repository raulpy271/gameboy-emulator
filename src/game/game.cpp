
#include "game.h"

namespace gameboy {

Console::Console() {
  ppu.SetMemory(&mem);
}

void Console::initialize_registers() {
  cpu.reg.PC = 0x0100;
  cpu.reg.SP = 0xfffe;
}

void Console::run_a_instruction_cycle() {
  cpu.execute_intruction(&mem);
}

void Console::load_rom(Byte* rom) {
  for (int i = 0; i < (32 * 1024); i++) {
    mem.SetInAddr(i, rom[i]);
  }
}

}