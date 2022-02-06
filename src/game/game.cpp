
#include "game.h"

namespace gameboy {

void Console::initialize_registers() {
  cpu.reg.PC = 0x0100;
  cpu.reg.SP = 0xfffe;
}

}