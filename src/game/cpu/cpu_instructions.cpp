
#include <utility>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

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
  mem->SetInAddr(reg.SP - 1, reg.B);
  mem->SetInAddr(reg.SP - 2, reg.C);
  reg.SP = reg.SP - 2;
  reg.PC = reg.PC + 1;
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

void CPU::LD_DE_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.D, &reg.E);
}

void CPU::LD_HL_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.H, &reg.L);
}

void CPU::LD_BC_d16_Instruction(Memory* mem) {
  LD_XX_d16_Instruction(mem, &reg.PC, &reg.B, &reg.C);
}

void CPU::LD_A_aDE_Instruction(Memory* mem) {
  Address add_of_value_to_load_in_A = utils::create_address_from_two_bytes(reg.D, reg.E);
  reg.A = mem->GetInAddr(add_of_value_to_load_in_A);
  reg.PC += 1;
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

void CPU::INC_DE_Instruction(Memory* mem) {
  utils::increment_registers_pair(&reg.D, &reg.E);
  reg.PC += 1;
}

void CPU::DEC_BC_Instruction(Memory* mem) {
  utils::decrement_registers_pair(&reg.B, &reg.C);
  reg.PC += 1;
}

void CPU::LD_A_B_Instruction(Memory* mem) {
  reg.A = reg.B;
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
  std::pair<Byte, Byte> PC_pair = utils::create_two_bytes_from_address(addr_after_return);
  mem->SetInAddr(reg.SP - 1, PC_pair.first);
  mem->SetInAddr(reg.SP - 2, PC_pair.second);
  reg.SP -= 2;
  reg.PC = next_addr;
}

void CPU::RET_Instruction(Memory* mem) {
  Byte lower_byte =  mem->GetInAddr(reg.SP);
  Byte higher_byte = mem->GetInAddr(reg.SP + 1);
  reg.SP += 2;
  Address next_addr = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.PC = next_addr;
}

void CPU::JR_s8_Instruction(Memory* mem) {
  Byte steps = mem->GetInAddr(reg.PC + 1);
  reg.PC = reg.PC + 2 + steps;
}

}