
#include <iostream>
#include <bitset>

#include "cpu.h"
#include "opcodes.h"
#include "../hardware_registers.h"
#include "cb_prefixed_opcodes.h"
#include "interrupts.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"

namespace gameboy {

bool CPU::GetIME() {
  return IME;
}

InterruptFlag CPU::GetNextInterrupt(Memory* mem) {
  if (IME) {
    std::bitset<8> interruption_possible = mem->GetInAddr(rIE) & mem->GetInAddr(rIF);
    for (int i = 0; i < 8; i++) {
      if (interruption_possible[i]) {
        return (InterruptFlag) i;
      }
    }
    return InterruptFlag::NoInterrupt;
  } else {
    return InterruptFlag::NoInterrupt;
  }
}

void CPU::execute_interrupt(Memory* mem, InterruptFlag interrupt) {
  Address interrupt_handler = utils::GetInterruptHandlingAddress(interrupt);
  PUSH_PC_Instruction(mem, &reg.SP, reg.PC);
  IME = false;
  std::bitset<8> IF_bitset(mem->GetInAddr(rIF));
  IF_bitset[(int) interrupt] = false;
  mem->SetInAddr(rIF, IF_bitset.to_ulong());
  reg.PC = interrupt_handler;
  execute_intruction(mem);
}

void CPU::execute_intruction(Memory* mem) {
  Byte opcode = mem->GetInAddr(reg.PC);
  switch (opcode)
  {
  case (NOP):
    CPU::HALT_Instruction(mem);
    break;

  case (HALT):
    CPU::HALT_Instruction(mem);
    break;

  case (IE):
    CPU::IE_Instruction(mem);
    break;

  case (DI):
    CPU::DI_Instruction(mem);
    break;

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

  case (LD_A_a8):
    CPU::LD_A_a8_Instruction(mem);
    break;

  case (CP_d8):
    CPU::CP_d8_Instruction(mem);
    break;

  case (PUSH_AF):
    CPU::PUSH_AF_Instruction(mem);
    break;

  case (PUSH_DE):
    CPU::PUSH_DE_Instruction(mem);
    break;

  case (PUSH_BC):
    CPU::PUSH_BC_Instruction(mem);
    break;

  case (PUSH_HL):
    CPU::PUSH_HL_Instruction(mem);
    break;

  case (POP_HL):
    CPU::POP_HL_Instruction(mem);
    break;

  case (POP_DE):
    CPU::POP_DE_Instruction(mem);
    break;

  case (POP_BC):
    CPU::POP_BC_Instruction(mem);
    break;

  case (POP_AF):
    CPU::POP_AF_Instruction(mem);
    break;

  case (JP_C_a16):
    CPU::JP_C_a16_Instruction(mem);
    break;

  case (JP_NC_a16):
    CPU::JP_NC_a16_Instruction(mem);
    break;

  case (LD_DE_d16):
    CPU::LD_DE_d16_Instruction(mem);
    break;

  case (LD_HL_d16):
    CPU::LD_HL_d16_Instruction(mem);
    break;

  case (LD_SP_d16):
    CPU::LD_SP_d16_Instruction(mem);
    break;

  case (LD_BC_d16):
    CPU::LD_BC_d16_Instruction(mem);
    break;

  case (LD_A_aDE):
    CPU::LD_A_aDE_Instruction(mem);
    break;

  case (LD_A_aHL):
    CPU::LD_A_aHL_Instruction(mem);
    break;

  case (LD_A_aHLI):
    CPU::LD_A_aHLI_Instruction(mem);
    break;

  case (LD_aHLI_A):
    CPU::LD_aHLI_A_Instruction(mem);
    break;

  case (LD_aHLD_A):
    CPU::LD_aHLD_A_Instruction(mem);
    break;

  case (LD_aHL_d8):
    CPU::LD_aHL_d8_Instruction(mem);
    break;

  case (LD_aHL_A):
    CPU::LD_aHL_A_Instruction(mem);
    break;

  case (INC_DE):
    CPU::INC_DE_Instruction(mem);
    break;

  case (INC_A):
    CPU::INC_A_Instruction(mem);
    break;

  case (INC_B):
    CPU::INC_B_Instruction(mem);
    break;

  case (INC_C):
    CPU::INC_C_Instruction(mem);
    break;

  case (INC_D):
    CPU::INC_D_Instruction(mem);
    break;

  case (INC_E):
    CPU::INC_E_Instruction(mem);
    break;

  case (INC_H):
    CPU::INC_H_Instruction(mem);
    break;

  case (INC_L):
    CPU::INC_L_Instruction(mem);
    break;

  case (INC_aHL):
    CPU::INC_aHL_Instruction(mem);
    break;

  case (INC_HL):
    CPU::INC_HL_Instruction(mem);
    break;

  case (DEC_BC):
    CPU::DEC_BC_Instruction(mem);
    break;

  case (DEC_A):
    CPU::DEC_A_Instruction(mem);
    break;

  case (DEC_B):
    CPU::DEC_B_Instruction(mem);
    break;

  case (DEC_C):
    CPU::DEC_C_Instruction(mem);
    break;

  case (LD_A_B):
    CPU::LD_A_B_Instruction(mem);
    break;

  case (LD_A_L):
    CPU::LD_A_L_Instruction(mem);
    break;

  case (LD_H_A):
    CPU::LD_H_A_Instruction(mem);
    break;

  case (LD_L_A):
    CPU::LD_L_A_Instruction(mem);
    break;

  case (LD_A_C):
    CPU::LD_A_C_Instruction(mem);
    break;

  case (LD_A_H):
    CPU::LD_A_H_Instruction(mem);
    break;

  case (LD_C_A):
    CPU::LD_C_A_Instruction(mem);
    break;

  case (LD_D_A):
    CPU::LD_D_A_Instruction(mem);
    break;

  case (LD_B_A):
    CPU::LD_B_A_Instruction(mem);
    break;

  case (LD_B_B):
    CPU::LD_B_B_Instruction(mem);
    break;

  case (LD_B_C):
    CPU::LD_B_C_Instruction(mem);
    break;

  case (LD_B_D):
    CPU::LD_B_D_Instruction(mem);
    break;

  case (LD_B_E):
    CPU::LD_B_E_Instruction(mem);
    break;

  case (LD_B_H):
    CPU::LD_B_H_Instruction(mem);
    break;

  case (LD_B_L):
    CPU::LD_B_L_Instruction(mem);
    break;

  case (LD_B_aHL):
    CPU::LD_B_aHL_Instruction(mem);
    break;

  case (ADD_A_B):
    CPU::ADD_A_B_Instruction(mem);
    break;

  case (ADD_A_d8):
    CPU::ADD_A_d8_Instruction(mem);
    break;

  case (SUB_A_B):
    CPU::SUB_A_B_Instruction(mem);
    break;

  case (ADD_HL_BC):
    CPU::ADD_HL_BC_Instruction(mem);
    break;

  case (OR_A_C):
    CPU::OR_A_C_Instruction(mem);
    break;

  case (OR_A_B):
    CPU::OR_A_B_Instruction(mem);
    break;

  case (AND_A_A):
    CPU::AND_A_A_Instruction(mem);
    break;

  case (AND_A_C):
    CPU::AND_A_C_Instruction(mem);
    break;

  case (AND_A_d8):
    CPU::AND_A_d8_Instruction(mem);
    break;

  case (XOR_A_A):
    CPU::XOR_A_A_Instruction(mem);
    break;

  case (XOR_A_C):
    CPU::XOR_A_C_Instruction(mem);
    break;

  case (JP_NZ_a16):
    CPU::JP_NZ_a16_Instruction(mem);
    break;

  case (JR_NZ_s8):
    CPU::JR_NZ_s8_Instruction(mem);
    break;

  case (JR_Z_s8):
    CPU::JR_Z_s8_Instruction(mem);
    break;

  case (JP_Z_a16):
    CPU::JP_Z_a16_Instruction(mem);
    break;

  case (CALL_a16):
    CPU::CALL_a16_Instruction(mem);
    break;

  case (CALL_Z_a16):
    CPU::CALL_Z_a16_Instruction(mem);
    break;

  case (CALL_NZ_a16):
    CPU::CALL_NZ_a16_Instruction(mem);
    break;

  case (CALL_C_a16):
    CPU::CALL_C_a16_Instruction(mem);
    break;

  case (RET):
    CPU::RET_Instruction(mem);
    break;

  case (RETI):
    CPU::RETI_Instruction(mem);
    break;

  case (RET_Z):
    CPU::RET_Z_Instruction(mem);
    break;

  case (RET_NZ):
    CPU::RET_NZ_Instruction(mem);
    break;

  case (RET_NC):
    CPU::RET_NC_Instruction(mem);
    break;

  case (JR_s8):
    CPU::JR_s8_Instruction(mem);
    break;

  case (CCF):
    CPU::CCF_Instruction(mem);
    break;

  case (CPL):
    CPU::CPL_Instruction(mem);
    break;

  case (RST_0x28):
    CPU::RST_0x28_Instruction(mem);
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
  case (BIT_0_A):
    CPU::BIT_0_A_Instruction(mem);
    break;

  case (BIT_1_A):
    CPU::BIT_1_A_Instruction(mem);
    break;

  case (BIT_2_A):
    CPU::BIT_2_A_Instruction(mem);
    break;

  case (BIT_3_A):
    CPU::BIT_3_A_Instruction(mem);
    break;

  case (RR_A):
    CPU::RR_A_Instruction(mem);
    break;

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

  case (SRL_A):
    CPU::SRL_A_Instruction(mem);
    break;

  case (SRL_B):
    CPU::SRL_B_Instruction(mem);
    break;

  case (SWAP_A):
    CPU::SWAP_A_Instruction(mem);
    break;

  default:
    std::cout << "Invalid prefixed opcode: " << (unsigned int) opcode << std::endl;
    break;
  }

}

}