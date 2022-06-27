
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
  instructions[SUB_A_B] = 1;
  instructions[SUB_A_d8] = 2;
  instructions[SUB_A_aHL] = 1;
  instructions[SBC_A_C] = 1;
  instructions[SBC_A_d8] = 2;
  instructions[DEC_A] = 1;
  instructions[DEC_B] = 1;
  instructions[DEC_C] = 1;
  instructions[DEC_E] = 1;
  instructions[DEC_H] = 1;
  instructions[DEC_L] = 1;
  instructions[DEC_BC] = 1;
  instructions[DEC_DE] = 1;
  instructions[DEC_HL] = 1;
  instructions[CP_A_C] = 1;
  instructions[CP_d8] = 2;
  instructions[CP_A_aHL] = 1;
  instructions[LD_H_d8] = 2;
  instructions[ADD_A_A] = 1;
  instructions[ADD_A_B] = 1;
  instructions[ADD_A_D] = 1;
  instructions[ADD_A_L] = 1;
  instructions[ADC_A_C] = 1;
  instructions[OR_A_B] = 1;
  instructions[OR_A_C] = 1;
  instructions[OR_A_D] = 1;
  instructions[OR_A_d8] = 2;
}

unsigned int InstructionsSize::GetSize(int opcode, bool CBPrefix) {
  if (CBPrefix) {
    return 2;
  } else {
    return instructions[opcode];
  }
}

}