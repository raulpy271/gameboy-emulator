
#include <iostream>

#include "cpu.h"
#include "opcodes.h"
#include "cb_prefixed_opcodes.h"

namespace gameboy {

void CPU::execute_intruction(Memory* mem) {
  Byte opcode = mem->GetInAddr(reg.PC);
  switch (opcode)
  {
  case (JP_a16):
    CPU::JP_a16_Instruction(mem);
    break;
  
  case (LD_d8):
    CPU::LD_d8_Instruction(mem);
    break;

  case (LD_B_d8):
    CPU::LD_B_d8_Instruction(mem);
    break;

  case (LD_C_d8):
    CPU::LD_C_d8_Instruction(mem);
    break;

  case (LD_a8_A):
    CPU::LD_a8_A_Instruction(mem);
    break;

  case (LD_a16_A):
    CPU::LD_a16_A_Instruction(mem);
    break;

  case (LD_aC_A):
    CPU::LD_aC_A_Instruction(mem);
    break;

  case (LD_A_a16):
    CPU::LD_A_a16_Instruction(mem);
    break;

  case (CP_d8):
    CPU::CP_d8_Instruction(mem);
    break;

  case (PUSH_BC):
    CPU::PUSH_BC_Instruction(mem);
    break;

  case (JP_C_a16):
    CPU::JP_C_a16_Instruction(mem);
    break;

  case (LD_DE_d16):
    CPU::LD_DE_d16_Instruction(mem);
    break;

  case (LD_HL_d16):
    CPU::LD_HL_d16_Instruction(mem);
    break;

  case (LD_BC_d16):
    CPU::LD_BC_d16_Instruction(mem);
    break;

  case (LD_A_aDE):
    CPU::LD_A_aDE_Instruction(mem);
    break;

  case (LD_aHLI_A):
    CPU::LD_aHLI_A_Instruction(mem);
    break;

  case (LD_aHL_A):
    CPU::LD_aHL_A_Instruction(mem);
    break;

  case (INC_DE):
    CPU::INC_DE_Instruction(mem);
    break;

  case (INC_HL):
    CPU::INC_HL_Instruction(mem);
    break;

  case (DEC_BC):
    CPU::DEC_BC_Instruction(mem);
    break;

  case (LD_A_B):
    CPU::LD_A_B_Instruction(mem);
    break;

  case (LD_A_C):
    CPU::LD_A_C_Instruction(mem);
    break;

  case (OR_A_C):
    CPU::OR_A_C_Instruction(mem);
    break;

  case (OR_A_B):
    CPU::OR_A_B_Instruction(mem);
    break;

  case (XOR_A_A):
    CPU::XOR_A_A_Instruction(mem);
    break;

  case (JP_NZ_a16):
    CPU::JP_NZ_a16_Instruction(mem);
    break;

  case (JR_NZ_s8):
    CPU::JR_NZ_s8_Instruction(mem);
    break;

  case (JP_Z_a16):
    CPU::JP_Z_a16_Instruction(mem);
    break;

  case (CALL_a16):
    CPU::CALL_a16_Instruction(mem);
    break;

  case (RET):
    CPU::RET_Instruction(mem);
    break;

  case (JR_s8):
    CPU::JR_s8_Instruction(mem);
    break;

  case (OPCODE_PREFIX):
    CPU::execute_prefixed_instruction(mem);
    break;

  default:
    std::cout << "Invalid opcode: " << (unsigned int) opcode << std::endl;
    std::cout << "After opcode: " << (unsigned int) mem->GetInAddr(reg.PC + 1) << std::endl;
    break;
  }
}

void CPU::execute_prefixed_instruction(Memory* mem) {
  Byte opcode = mem->GetInAddr(reg.PC + 1);
  switch (opcode)
  {
  case (RES_7_aHL):
    CPU::RES_7_aHL_Instruction(mem);
    break;

  case (RES_1_aHL):
    CPU::RES_1_aHL_Instruction(mem);
    break;

  case (SET_7_aHL):
    CPU::SET_7_aHL_Instruction(mem);
    break;

  case (SET_4_aHL):
    CPU::SET_4_aHL_Instruction(mem);
    break;

  case (SET_1_aHL):
    CPU::SET_1_aHL_Instruction(mem);
    break;

  case (SET_0_aHL):
    CPU::SET_0_aHL_Instruction(mem);
    break;

  default:
    std::cout << "Invalid prefixed opcode: " << (unsigned int) opcode << std::endl;
    break;
  }

}

}