
#include <bitset>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::RES_0_A_Instruction(Memory* mem) {
  std::bitset<8> A_bitset(reg.A);
  A_bitset.set(0, false);
  reg.A = A_bitset.to_ulong();
}

void CPU::BIT_7_aHL_Instruction(Memory* mem) {
  Address addr = utils::create_address_from_two_bytes(reg.H, reg.L);
  Byte value = mem->GetInAddr(addr);
  BIT_X_A_Instruction(&reg.F, value, &reg.PC, 7);
}

void CPU::RR_A_Instruction(Memory* mem) {
  bool carry = utils::carry_flag(&reg.F);
  bool reg_A_end_with_zero = reg.A % 2 == 0;
  reg.F = 0;
  reg.A = reg.A >> 1 | (carry << 7);
  utils::set_carry_flag(&reg.F, !reg_A_end_with_zero);
  utils::set_zero_flag(&reg.F, !(bool)reg.A);
}

void CPU::RES_0_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, false, 0);
}

void CPU::RES_7_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, false, 7);
}

void CPU::RES_1_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, false, 1);
}

void CPU::SET_7_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 7);
}

void CPU::SET_4_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 4);
}

void CPU::SET_1_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 1);
}

void CPU::SET_0_aHL_Instruction(Memory* mem) {
  ChangeBitValueFromMemory_Instruction(mem, reg.H, reg.L, true, 0);
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
}

void CPU::SLA_A_Instruction(Memory* mem) {
  reg.F = 0;
  bool last_bit_set = reg.A & 0b10000000;
  if (last_bit_set) {
    utils::set_carry_flag(&reg.F, true);
  } else {
    utils::set_carry_flag(&reg.F, false);
  }
  reg.A = reg.A << 1;
  if (reg.A == 0) {
    utils::set_zero_flag(&reg.F, true);
  }
}

}