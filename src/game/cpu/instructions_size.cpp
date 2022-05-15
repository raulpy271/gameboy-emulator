
#include <iostream>

#include "instructions_size.h"

namespace gameboy {

InstructionsSize::InstructionsSize() : instructions{0} {
}

unsigned int InstructionsSize::GetSize(int opcode, bool CBPrefix) {
  if (CBPrefix) {
    return 2;
  } else {
    return instructions[opcode];
  }
}

}