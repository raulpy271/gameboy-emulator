
#ifndef GAME_CPU_H_
#define GAME_CPU_H_

#include "primitives.h"
#include "opcodes.h"
#include "memory.h"

namespace gameboy {

struct Registers {
  Byte A, F;
  Byte B, C;
  Byte D, E;
  Byte H, L;
  Address SP;
  Address PC;
};

class CPU {
 private:
  void JP_a16_Instruction(Memory* mem);
  void LD_d8_Instruction(Memory* mem);
  void LD_a16_A_Instruction(Memory* mem);
  void LD_A_a16_Instruction(Memory* mem);
  void CP_d8_Instruction(Memory* mem);
  void PUSH_BC_Instruction(Memory* mem);

 public:
  struct Registers reg;

  void execute_intruction(Memory* mem);
};

}

#endif  // GAME_CPU_H_
