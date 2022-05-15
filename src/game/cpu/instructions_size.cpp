
#include <iostream>

#include "instructions_size.h"

namespace gameboy {

InstructionsSize::InstructionsSize() : instructions{0} {
  instructions[LD_d8] = 2;
  instructions[LD_B_d8] = 2;
  instructions[LD_C_d8] = 2;
  instructions[LD_D_d8] = 2;
  instructions[LD_E_d8] = 2;
  instructions[RLCA] = 1;
}

unsigned int InstructionsSize::GetSize(int opcode, bool CBPrefix) {
  if (CBPrefix) {
    return 2;
  } else {
    return instructions[opcode];
  }
}

}