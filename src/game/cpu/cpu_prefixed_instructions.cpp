
#include <bitset>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::BIT_0_A_Instruction(Memory* mem) {
  BIT_X_A_Instruction(&reg.F, reg.A, &reg.PC, 0);
}

void CPU::BIT_1_A_Instruction(Memory* mem) {
  BIT_X_A_Instruction(&reg.F, reg.A, &reg.PC, 1);
}

void CPU::BIT_2_A_Instruction(Memory* mem) {
  BIT_X_A_Instruction(&reg.F, reg.A, &reg.PC, 2);
}

void CPU::BIT_3_A_Instruction(Memory* mem) {
  BIT_X_A_Instruction(&reg.F, reg.A, &reg.PC, 3);
}

void CPU::RR_A_Instruction(Memory* mem) {
  bool carry = utils::carry_flag(&reg.F);
  bool reg_A_end_with_zero = reg.A % 2 == 0;
  reg.F = 0;
  reg.A = reg.A >> 1 | (carry << 7);
  utils::set_carry_flag(&reg.F, !reg_A_end_with_zero);
  utils::set_zero_flag(&reg.F, !(bool)reg.A);
  reg.PC += 2;
}

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

void CPU::SRL_B_Instruction(Memory* mem) {
  bool reg_B_end_with_zero = reg.B % 2 == 0;
  if (reg_B_end_with_zero) {
    reg.F = 0b00000000; // Setting Carry flag to zero
  } else {
    reg.F = 0b00010000; // Setting Carry flag to one
  }
  reg.B = reg.B >> 1;
  if (reg.B == 0) {
    utils::set_zero_flag(&reg.F, true);
  }
  reg.PC += 2;
}

}