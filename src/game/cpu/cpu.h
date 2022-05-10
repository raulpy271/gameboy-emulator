
#ifndef GAME_CPU_H_
#define GAME_CPU_H_

#include "../primitives.h"
#include "../memory.h"
#include "interrupts.h"

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
  bool IME = false;

  void HALT_Instruction(Memory* mem);
  void IE_Instruction(Memory* mem);
  void DI_Instruction(Memory* mem);
  void JP_a16_Instruction(Memory* mem);
  void JP_HL_Instruction(Memory* mem);
  void LD_d8_Instruction(Memory* mem);
  void LD_B_d8_Instruction(Memory* mem);
  void LD_C_d8_Instruction(Memory* mem);
  void LD_D_d8_Instruction(Memory* mem);
  void LD_a8_A_Instruction(Memory* mem);
  void LD_a16_A_Instruction(Memory* mem);
  void LD_A_a16_Instruction(Memory* mem);
  void LD_A_a8_Instruction(Memory* mem);
  void CP_d8_Instruction(Memory* mem);
  void PUSH_AF_Instruction(Memory* mem);
  void PUSH_DE_Instruction(Memory* mem);
  void PUSH_HL_Instruction(Memory* mem);
  void PUSH_BC_Instruction(Memory* mem);
  void POP_HL_Instruction(Memory* mem);
  void POP_DE_Instruction(Memory* mem);
  void POP_BC_Instruction(Memory* mem);
  void POP_AF_Instruction(Memory* mem);
  void JP_C_a16_Instruction(Memory* mem);
  void LD_DE_d16_Instruction(Memory* mem);
  void LD_HL_d16_Instruction(Memory* mem);
  void LD_SP_d16_Instruction(Memory* mem);
  void LD_BC_d16_Instruction(Memory* mem);
  void LD_A_aBC_Instruction(Memory* mem);
  void LD_A_aDE_Instruction(Memory* mem);
  void LD_A_aHL_Instruction(Memory* mem);
  void LD_A_aHLI_Instruction(Memory* mem);
  void LD_A_aHLD_Instruction(Memory* mem);
  void LD_aC_A_Instruction(Memory* mem);
  void LD_aHLI_A_Instruction(Memory* mem);
  void LD_aHLD_A_Instruction(Memory* mem);
  void LD_aHL_d8_Instruction(Memory* mem);
  void LD_aDE_A_Instruction(Memory* mem);
  void LD_aHL_A_Instruction(Memory* mem);
  void INC_A_Instruction(Memory* mem);
  void INC_B_Instruction(Memory* mem);
  void INC_C_Instruction(Memory* mem);
  void INC_D_Instruction(Memory* mem);
  void INC_E_Instruction(Memory* mem);
  void INC_H_Instruction(Memory* mem);
  void INC_L_Instruction(Memory* mem);
  void INC_aHL_Instruction(Memory* mem);
  void INC_BC_Instruction(Memory* mem);
  void INC_DE_Instruction(Memory* mem);
  void INC_HL_Instruction(Memory* mem);
  void DEC_A_Instruction(Memory* mem);
  void DEC_B_Instruction(Memory* mem);
  void DEC_C_Instruction(Memory* mem);
  void DEC_aHL_Instruction(Memory* mem);
  void DEC_BC_Instruction(Memory* mem);
  void LD_A_B_Instruction(Memory* mem);
  void LD_A_E_Instruction(Memory* mem);
  void LD_H_A_Instruction(Memory* mem);
  void LD_H_B_Instruction(Memory* mem);
  void LD_L_A_Instruction(Memory* mem);
  void LD_L_C_Instruction(Memory* mem);
  void LD_A_C_Instruction(Memory* mem);
  void LD_A_L_Instruction(Memory* mem);
  void LD_A_H_Instruction(Memory* mem);
  void LD_C_A_Instruction(Memory* mem);
  void LD_D_A_Instruction(Memory* mem);
  void LD_E_A_Instruction(Memory* mem);
  void LD_B_A_Instruction(Memory* mem);
  void LD_B_B_Instruction(Memory* mem);
  void LD_B_C_Instruction(Memory* mem);
  void LD_B_D_Instruction(Memory* mem);
  void LD_B_E_Instruction(Memory* mem);
  void LD_B_H_Instruction(Memory* mem);
  void LD_B_L_Instruction(Memory* mem);
  void LD_B_aHL_Instruction(Memory* mem);
  void LD_C_aHL_Instruction(Memory* mem);
  void LD_D_aHL_Instruction(Memory* mem);
  void LD_E_aHL_Instruction(Memory* mem);
  void ADD_A_A_Instruction(Memory* mem);
  void ADD_A_B_Instruction(Memory* mem);
  void ADD_A_L_Instruction(Memory* mem);
  void ADD_A_d8_Instruction(Memory* mem);
  void SUB_A_B_Instruction(Memory* mem);
  void ADD_HL_BC_Instruction(Memory* mem);
  void ADD_HL_DE_Instruction(Memory* mem);
  void OR_A_B_Instruction(Memory* mem);
  void AND_A_A_Instruction(Memory* mem);
  void AND_A_C_Instruction(Memory* mem);
  void AND_A_d8_Instruction(Memory* mem);
  void OR_A_C_Instruction(Memory* mem);
  void XOR_A_A_Instruction(Memory* mem);
  void XOR_A_C_Instruction(Memory* mem);
  void JR_NZ_s8_Instruction(Memory* mem);
  void JR_Z_s8_Instruction(Memory* mem);
  void JP_NZ_a16_Instruction(Memory* mem);
  void JP_Z_a16_Instruction(Memory* mem);
  void JP_NC_a16_Instruction(Memory* mem);
  void CALL_a16_Instruction(Memory* mem);
  void CALL_Z_a16_Instruction(Memory* mem);
  void CALL_NZ_a16_Instruction(Memory* mem);
  void CALL_C_a16_Instruction(Memory* mem);
  void RET_Instruction(Memory* mem);
  void RETI_Instruction(Memory* mem);
  void RET_Z_Instruction(Memory* mem);
  void RET_NZ_Instruction(Memory* mem);
  void RET_NC_Instruction(Memory* mem);
  void JR_s8_Instruction(Memory* mem);
  void CCF_Instruction(Memory* mem);
  void CPL_Instruction(Memory* mem);
  void RST_0x28_Instruction(Memory* mem);
  

  void execute_prefixed_instruction(Memory* mem);


  void BIT_0_A_Instruction(Memory* mem);
  void RES_0_A_Instruction(Memory* mem);
  void BIT_1_A_Instruction(Memory* mem);
  void BIT_2_A_Instruction(Memory* mem);
  void BIT_3_A_Instruction(Memory* mem);
  void RR_A_Instruction(Memory* mem);
  void RES_7_aHL_Instruction(Memory* mem);
  void RES_1_aHL_Instruction(Memory* mem);
  void SET_7_aHL_Instruction(Memory* mem);
  void SET_4_aHL_Instruction(Memory* mem);
  void SET_1_aHL_Instruction(Memory* mem);
  void SET_0_aHL_Instruction(Memory* mem);
  void SRL_A_Instruction(Memory* mem);
  void SRL_B_Instruction(Memory* mem);
  void SLA_A_Instruction(Memory* mem);
  void SWAP_A_Instruction(Memory* mem);

 public:
  struct Registers reg;

  void execute_intruction(Memory* mem);

  void execute_interrupt(Memory* mem, InterruptFlag interrupt);

  InterruptFlag GetNextInterrupt(Memory* mem);

  bool GetIME();
};

}

#endif  // GAME_CPU_H_
