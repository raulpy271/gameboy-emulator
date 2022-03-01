
#include <bitset>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::RES_7_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, false, 7);
  reg.PC += 2;
}

void CPU::RES_1_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, false, 1);
  reg.PC += 2;
}

void CPU::SET_7_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 7);
  reg.PC += 2;
}

void CPU::SET_4_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 4);
  reg.PC += 2;
}

void CPU::SET_1_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 1);
  reg.PC += 2;
}

void CPU::SET_0_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 0);
  reg.PC += 2;
}

void CPU::SRL_A_Instruction(Memory* mem) {
  bool reg_A_end_with_zero = reg.A % 2 == 0;
  if (reg_A_end_with_zero) {
    reg.F = 0b00000000; // Setting Carry flag to zero
  } else {
    reg.F = 0b00010000; // Setting Carry flag to one
  }
  reg.A = reg.A >> 1;
  if (reg.A == 0) {
    utils::set_zero_flag(&reg.F, true);
  }
  reg.PC += 2;
}

}