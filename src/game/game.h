
#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

#include "primitives.h"
#include "memory.h"
#include "cpu.h"

namespace gameboy {

class Console {
 public:
  Memory mem;
  CPU cpu;

  void initialize_registers();
};

}

#endif  // GAME_CONSOLE_H_