
#include <utility>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::HALT_Instruction(Memory* mem) {
  reg.PC += 1;
}

void CPU::IE_Instruction(Memory* mem) {
  IME = true;
  reg.PC += 1;
}

void CPU::DI_Instruction(Memory* mem) {
  IME = false;
  reg.PC += 1;
}

void CPU::JP_a16_Instruction(Memory* mem) {
  Address lower_byte_addr = reg.PC + 1;
  Address higher_byte_addr = reg.PC + 2;
  Byte lower_byte = mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  Address addr_to_jump = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.PC = addr_to_jump;
}

void CPU::LD_d8_Instruction(Memory* mem) {
  LD_X_d8_Instruction(mem, &reg.PC, &reg.A);
}

void CPU::LD_B_d8_Instruction(Memory* mem) {
  LD_X_d8_Instruction(mem, &reg.PC, &reg.B);
}

void CPU::LD_C_d8_Instruction(Memory* mem) {
  LD_X_d8_Instruction(mem, &reg.PC, &reg.C);
}

void CPU::LD_a16_A_Instruction(Memory* mem) {
  Address lower_byte_addr = reg.PC + 1;
  Address higher_byte_addr = reg.PC + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  Address addr_to_load_A = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  mem->SetInAddr(addr_to_load_A, reg.A);
  reg.PC = reg.PC + 3;
}

void CPU::LD_a8_A_Instruction(Memory* mem) {
  Address lower_byte_addr = reg.PC + 1;
  Byte lower_byte = mem->GetInAddr(lower_byte_addr);
  mem->SetInAddr(0xFF00 + lower_byte, reg.A);
  reg.PC = reg.PC + 2;
}

void CPU::LD_aC_A_Instruction(Memory* mem) {
  Address addr_to_store_A = 0xFF00 + reg.C;
  mem->SetInAddr(addr_to_store_A, reg.A);
  reg.PC = reg.PC + 1;
}

void CPU::LD_A_a16_Instruction(Memory* mem) {
  Address lower_byte_addr = reg.PC + 1;
  Address higher_byte_addr = reg.PC + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  Address addr_to_load_A = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.A = mem->GetInAddr(addr_to_load_A);
  reg.PC = reg.PC + 3;
}

void CPU::LD_A_a8_Instruction(Memory* mem) {
  Address lower_byte_addr = reg.PC + 1;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Address addr_to_load_A = utils::create_address_from_two_bytes(0xff, lower_byte);
  reg.A = mem->GetInAddr(addr_to_load_A);
  reg.PC = reg.PC + 2;
}

void CPU::CP_d8_Instruction(Memory* mem) {
  Address byte_to_compare_address = reg.PC + 1;
  Byte byte_to_compare =  mem->GetInAddr(byte_to_compare_address);
  reg.F = 0;
  if (byte_to_compare == reg.A) {
    utils::set_zero_flag(&reg.F, true);
  } else {
    utils::set_zero_flag(&reg.F, false);
  }
  reg.PC = reg.PC + 2;
}

void CPU::PUSH_BC_Instruction(Memory* mem) {
  PUSH_XX_Instruction(mem, &reg.SP, reg.B, reg.C, &reg.PC);
}

void CPU::PUSH_DE_Instruction(Memory* mem) {
  PUSH_XX_Instruction(mem, &reg.SP, reg.D, reg.E, &reg.PC);
}

void CPU::PUSH_AF_Instruction(Memory* mem) {
  PUSH_XX_Instruction(mem, &reg.SP, reg.A, reg.F, &reg.PC);
}

void CPU::PUSH_HL_Instruction(Memory* mem) {
  PUSH_XX_Instruction(mem, &reg.SP, reg.H, reg.L, &reg.PC);
}

void CPU::POP_HL_Instruction(Memory* mem) {
  POP_XX_Instruction(mem, &reg.SP, &reg.H, &reg.L, &reg.PC);
}

void CPU::POP_DE_Instruction(Memory* mem) {
  POP_XX_Instruction(mem, &reg.SP, &reg.D, &reg.E, &reg.PC);
}

void CPU::POP_BC_Instruction(Memory* mem) {
  POP_XX_Instruction(mem, &reg.SP, &reg.B, &reg.C, &reg.PC);
}

void CPU::POP_AF_Instruction(Memory* mem) {
  POP_XX_Instruction(mem, &reg.SP, &reg.A, &reg.F, &reg.PC);
}

void CPU::JP_C_a16_Instruction(Memory* mem) {
  if (utils::carry_flag(&reg.F)) {
    Address lower_byte_addr = reg.PC + 1;
    Address higher_byte_addr = reg.PC + 2;
    Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
    Byte higher_byte = mem->GetInAddr(higher_byte_addr);
    Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
    reg.PC = next_addr;
  } else {
    reg.PC = reg.PC + 3;
  }
}

void CPU::JP_NC_a16_Instruction(Memory* mem) {
  if (!utils::carry_flag(&reg.F)) {
    Address lower_byte_addr = reg.PC + 1;
    Address higher_byte_addr = reg.PC + 2;
    Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
    Byte higher_byte = mem->GetInAddr(higher_byte_addr);
    Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
    reg.PC = next_addr;
  } else {
    reg.PC = reg.PC + 3;
  }
}

void CPU::LD_DE_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.D, &reg.E);
}

void CPU::LD_HL_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.H, &reg.L);
}

void CPU::LD_BC_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.B, &reg.C);
}

void CPU::LD_SP_d16_Instruction(Memory* mem) {
  Address lower_byte_addr = (reg.PC) + 1;
  Address higher_byte_addr = (reg.PC) + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  Address addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.SP = addr;
  reg.PC = (reg.PC) + 3;
}

void CPU::LD_A_aDE_Instruction(Memory* mem) {
  Address add_of_value_to_load_in_A = utils::create_address_from_two_bytes(reg.D, reg.E);
  reg.A = mem->GetInAddr(add_of_value_to_load_in_A);
  reg.PC += 1;
}

void CPU::LD_A_aHL_Instruction(Memory* mem) {
  Address add_of_value_to_load_in_A = utils::create_address_from_two_bytes(reg.H, reg.L);
  reg.A = mem->GetInAddr(add_of_value_to_load_in_A);
  reg.PC += 1;
}

void CPU::LD_A_aHLI_Instruction(Memory* mem) {
  Address add_of_value_to_load_in_A = utils::create_address_from_two_bytes(reg.H, reg.L);
  reg.A = mem->GetInAddr(add_of_value_to_load_in_A);
  utils::increment_registers_pair(&reg.H, &reg.L);
  reg.PC += 1;
}

void CPU::LD_aHL_d8_Instruction(Memory* mem) {
  Address add_of_value_to_store = utils::create_address_from_two_bytes(reg.H, reg.L);
  Byte value = mem->GetInAddr(reg.PC + 1);
  mem->SetInAddr(add_of_value_to_store, value);
  reg.PC += 2;
}

void CPU::LD_aHL_A_Instruction(Memory* mem) {
  Address add_of_value_to_store_A = utils::create_address_from_two_bytes(reg.H, reg.L);
  mem->SetInAddr(add_of_value_to_store_A, reg.A);
  reg.PC += 1;
}

void CPU::LD_aHLI_A_Instruction(Memory* mem) {
  Address add_of_value_to_store_A = utils::create_address_from_two_bytes(reg.H, reg.L);
  mem->SetInAddr(add_of_value_to_store_A, reg.A);
  utils::increment_registers_pair(&reg.H, &reg.L);
  reg.PC += 1;
}

void CPU::LD_aHLD_A_Instruction(Memory* mem) {
  Address add_of_value_to_store_A = utils::create_address_from_two_bytes(reg.H, reg.L);
  mem->SetInAddr(add_of_value_to_store_A, reg.A);
  utils::decrement_registers_pair(&reg.H, &reg.L);
  reg.PC += 1;
}

void CPU::INC_A_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.A, &reg.F, &reg.PC);
}

void CPU::INC_B_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.B, &reg.F, &reg.PC);
}

void CPU::INC_C_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.C, &reg.F, &reg.PC);
}

void CPU::INC_D_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.D, &reg.F, &reg.PC);
}

void CPU::INC_E_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.E, &reg.F, &reg.PC);
}

void CPU::INC_H_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.H, &reg.F, &reg.PC);
}

void CPU::INC_L_Instruction(Memory* mem) {
  INC_X_Instruction(&reg.L, &reg.F, &reg.PC);
}

void CPU::INC_aHL_Instruction(Memory* mem) {
  Address aHL = utils::create_address_from_two_bytes(reg.H, reg.L);
  Byte value = mem->GetInAddr(aHL);
  if (((value) & 0xf) == 0xf) {
    utils::set_half_carry_flag(&reg.F, true);
  }
  value = value + 1;
  utils::set_subtract_flag(&reg.F, false);
  utils::set_zero_flag(&reg.F, !((bool)(value)));
  mem->SetInAddr(aHL, value);
  reg.PC += 1;
}

void CPU::INC_DE_Instruction(Memory* mem) {
  utils::increment_registers_pair(&reg.D, &reg.E);
  reg.PC += 1;
}

void CPU::INC_HL_Instruction(Memory* mem) {
  utils::increment_registers_pair(&reg.H, &reg.L);
  reg.PC += 1;
}

void CPU::DEC_BC_Instruction(Memory* mem) {
  utils::decrement_registers_pair(&reg.B, &reg.C);
  reg.PC += 1;
}

void CPU::DEC_A_Instruction(Memory* mem) {
  DEC_X_Instruction(&reg.A, &reg.F, &reg.PC);
}

void CPU::DEC_B_Instruction(Memory* mem) {
  DEC_X_Instruction(&reg.B, &reg.F, &reg.PC);
}

void CPU::DEC_C_Instruction(Memory* mem) {
  DEC_X_Instruction(&reg.C, &reg.F, &reg.PC);
}

void CPU::LD_A_B_Instruction(Memory* mem) {
  reg.A = reg.B;
  reg.PC += 1;
}

void CPU::LD_A_H_Instruction(Memory* mem) {
  reg.A = reg.H;
  reg.PC += 1;
}

void CPU::LD_H_A_Instruction(Memory* mem) {
  reg.H = reg.A;
  reg.PC += 1;
}

void CPU::LD_L_A_Instruction(Memory* mem) {
  reg.L = reg.A;
  reg.PC += 1;
}

void CPU::LD_A_C_Instruction(Memory* mem) {
  reg.A = reg.C;
  reg.PC += 1;
}

void CPU::LD_A_L_Instruction(Memory* mem) {
  reg.A = reg.L;
  reg.PC += 1;
}

void CPU::LD_C_A_Instruction(Memory* mem) {
  reg.C = reg.A;
  reg.PC += 1;
}

void CPU::LD_D_A_Instruction(Memory* mem) {
  reg.D = reg.A;
  reg.PC += 1;
}

void CPU::LD_B_A_Instruction(Memory* mem) {
  reg.B = reg.A;
  reg.PC += 1;
}

void CPU::LD_B_B_Instruction(Memory* mem) {
  reg.PC += 1;
}

void CPU::LD_B_C_Instruction(Memory* mem) {
  reg.B = reg.C;
  reg.PC += 1;
}

void CPU::LD_B_D_Instruction(Memory* mem) {
  reg.B = reg.D;
  reg.PC += 1;
}

void CPU::LD_B_E_Instruction(Memory* mem) {
  reg.B = reg.E;
  reg.PC += 1;
}

void CPU::LD_B_H_Instruction(Memory* mem) {
  reg.B = reg.H;
  reg.PC += 1;
}

void CPU::LD_B_L_Instruction(Memory* mem) {
  reg.B = reg.L;
  reg.PC += 1;
}

void CPU::LD_B_aHL_Instruction(Memory* mem) {
  Address add_of_value_to_load_in_B = utils::create_address_from_two_bytes(reg.H, reg.L);
  reg.B = mem->GetInAddr(add_of_value_to_load_in_B);
  reg.PC += 1;
}

void CPU::ADD_A_B_Instruction(Memory* mem) {
  ADD_X_Y_Instruction(&reg.A, &reg.B, &reg.F);
  reg.PC += 1;
}

void CPU::ADD_A_d8_Instruction(Memory* mem) {
  Byte value = mem->GetInAddr(reg.PC + 1);
  ADD_X_Y_Instruction(&reg.A, &value, &reg.F);
  reg.PC += 2;
}

void CPU::SUB_A_B_Instruction(Memory* mem) {
  reg.F = 0b01000000;
  Byte A_lower_part = reg.A & 0xf;
  Byte B_lower_part = reg.B & 0xf;
  if (reg.A < reg.B) {
    utils::set_carry_flag(&reg.F, true);
  }
  if ((A_lower_part) < (B_lower_part)) {
    utils::set_half_carry_flag(&reg.F, true);
  }
  reg.A = reg.A - reg.B;
  utils::set_zero_flag(&reg.F, !((bool)reg.A));
  reg.PC += 1;
}

void CPU::ADD_HL_BC_Instruction(Memory* mem) {
  Address HL = utils::create_address_from_two_bytes(reg.H, reg.L);
  Address BC = utils::create_address_from_two_bytes(reg.B, reg.C);
  std::pair<Byte, Byte> new_HL_pair = utils::create_two_bytes_from_address(HL + BC);
  reg.H = new_HL_pair.first;
  reg.L = new_HL_pair.second;
  reg.PC += 1;
}

void CPU::OR_A_B_Instruction(Memory* mem) {
  reg.A = reg.A | reg.B;
  reg.F = 0x0;
  if (reg.A == 0) {
    utils::set_zero_flag(&reg.F, true);
  }
  reg.PC += 1;
}

void CPU::AND_A_A_Instruction(Memory* mem) {
  if (reg.A == 0) {
    utils::set_zero_flag(&reg.F, true);
  } else {
    utils::set_zero_flag(&reg.F, false);
  }
  utils::set_subtract_flag(&reg.F, false);
  utils::set_half_carry_flag(&reg.F, true);
  utils::set_carry_flag(&reg.F, false);
  reg.PC += 1;
}

void CPU::OR_A_C_Instruction(Memory* mem) {
  reg.A = reg.A | reg.C;
  reg.F = 0x0;
  if (reg.A == 0) {
    utils::set_zero_flag(&reg.F, true);
  }
  reg.PC += 1;
}

void CPU::XOR_A_A_Instruction(Memory* mem) {
  reg.A = 0;
  reg.F = 0x0;
  utils::set_zero_flag(&reg.F, true);
  reg.PC += 1;
}

void CPU::JP_NZ_a16_Instruction(Memory* mem) {
  if (utils::zero_flag(&reg.F)) {
    reg.PC += 3;
  } else {
    Address lower_byte_addr = reg.PC + 1;
    Address higher_byte_addr = reg.PC + 2;
    Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
    Byte higher_byte = mem->GetInAddr(higher_byte_addr);
    Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
    reg.PC = next_addr;
  }
}


void CPU::JP_Z_a16_Instruction(Memory* mem) {
  if (!utils::zero_flag(&reg.F)) {
    reg.PC += 3;
  } else {
    Address lower_byte_addr = reg.PC + 1;
    Address higher_byte_addr = reg.PC + 2;
    Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
    Byte higher_byte = mem->GetInAddr(higher_byte_addr);
    Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
    reg.PC = next_addr;
  }
}

void CPU::CALL_a16_Instruction(Memory* mem) {
  Address addr_after_return = reg.PC + 3;
  Address lower_byte_addr = reg.PC + 1;
  Address higher_byte_addr = reg.PC + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  PUSH_PC_Instruction(mem, &reg.SP, addr_after_return);
  reg.PC = next_addr;
}

void CPU::CALL_Z_a16_Instruction(Memory* mem) {
  if (utils::zero_flag(&reg.F)) {
    CALL_a16_Instruction(mem);
  } else {
    reg.PC += 3;
  }
}

void CPU::CALL_NZ_a16_Instruction(Memory* mem) {
  if (!utils::zero_flag(&reg.F)) {
    CALL_a16_Instruction(mem);
  } else {
    reg.PC += 3;
  }
}

void CPU::CALL_C_a16_Instruction(Memory* mem) {
  if (utils::carry_flag(&reg.F)) {
    CALL_a16_Instruction(mem);
  } else {
    reg.PC += 3;
  }
}

void CPU::RET_Instruction(Memory* mem) {
  Byte lower_byte =  mem->GetInAddr(reg.SP);
  Byte higher_byte = mem->GetInAddr(reg.SP + 1);
  reg.SP += 2;
  Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.PC = next_addr;
}

void CPU::RETI_Instruction(Memory* mem) {
  IME = true;
  RET_Instruction(mem);
}

void CPU::RET_Z_Instruction(Memory* mem) {
  if (!utils::zero_flag(&reg.F)) {
    reg.PC += 1;
  } else {
    RET_Instruction(mem);
  }
}

void CPU::RET_NZ_Instruction(Memory* mem) {
  if (utils::zero_flag(&reg.F)) {
    reg.PC += 1;
  } else {
    RET_Instruction(mem);
  }
}

void CPU::RET_NC_Instruction(Memory* mem) {
  if (utils::carry_flag(&reg.F)) {
    reg.PC += 1;
  } else {
    RET_Instruction(mem);
  }
}

void CPU::JR_s8_Instruction(Memory* mem) {
  Byte steps = mem->GetInAddr(reg.PC + 1);
  reg.PC += 2;
  bool is_positive = steps < 0b10000000;
  if (is_positive) {
    reg.PC += steps;
  } else {
    steps = 0x100 - steps;
    reg.PC -= steps;
  }
}

void CPU::JR_Z_s8_Instruction(Memory* mem) {
  if (utils::zero_flag(&reg.F)) {
    JR_s8_Instruction(mem);
  } else {
    reg.PC += 2;
  }
}

void CPU::JR_NZ_s8_Instruction(Memory* mem) {
  if (!utils::zero_flag(&reg.F)) {
    JR_s8_Instruction(mem);
  } else {
    reg.PC += 2;
  }
}

void CPU::CCF_Instruction(Memory* mem) {
  bool carry_flag_value = utils::carry_flag(&reg.F);
  utils::set_carry_flag(&reg.F, !carry_flag_value);
  utils::set_half_carry_flag(&reg.F, false);
  utils::set_subtract_flag(&reg.F, false);
  reg.PC += 1;
}

void CPU::CPL_Instruction(Memory* mem) {
  reg.A = reg.A ^ 0xFF;
  utils::set_half_carry_flag(&reg.F, true);
  utils::set_subtract_flag(&reg.F, true);
  reg.PC += 1;
}

}