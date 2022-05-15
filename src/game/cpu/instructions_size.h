
#ifndef GAME_INSTRUCTIONS_SIZE_H_
#define GAME_INSTRUCTIONS_SIZE_H_

#include "opcodes.h"

namespace gameboy {

class InstructionsSize {
 public:
  InstructionsSize();

  unsigned int GetSize(int opcode, bool CBPrefix = false);

 private:
  unsigned int instructions[0x100];
};

}

#endif  // GAME_INSTRUCTIONS_SIZE_H_

