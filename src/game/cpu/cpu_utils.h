
#ifndef GAME_CPU_UTILS_H_
#define GAME_CPU_UTILS_H_

#include "../primitives.h"
#include "../memory.h"

#define BIT_X_R_MACRO(X, R) BIT_X_A_Instruction(&reg.F, reg.R, &reg.PC, X);

#define LD_R_d8_MACRO(R) LD_X_d8_Instruction(mem, &reg.PC, &reg.R);

#define ADD_X_Y_MACRO(X, Y) ADD_X_Y_Instruction(&reg.X, &reg.Y, &reg.F);

#define SWAP_X_MACRO(X) SWAP_X_Instruction(&reg.F, &reg.X);

#define DEC_X_Y_MACRO(X, Y) utils::decrement_registers_pair(&reg.X, &reg.Y);

#define DEC_X_MACRO(X) DEC_X_Instruction(&reg.X, &reg.F);

#define OR_X_Y_MACRO(X, Y) OR_X_Y_Instruction(&reg.X, &reg.Y, &reg.F);

#define CP_X_Y_MACRO(X, Y) SetSUBFlags(&reg.F, reg.X, reg.Y);

namespace gameboy {

void INC_X_Instruction(Byte* X, Byte* F, Address* PC);

void DEC_X_Instruction(Byte* X, Byte* F);

void OR_X_Y_Instruction(Byte* X, Byte* Y, Byte* F);

void ADD_X_Y_Instruction(Byte* X, Byte* Y, Byte* F);

void ADD_HL_XY_Instruction(Byte* H, Byte* L, Byte* X, Byte* Y, Byte* F, Address* PC);

void AND_X_Y_Instruction(Byte* X, Byte* Y, Byte* F, Address* PC);

void LD_XX_d16_Instruction(Memory* mem, Address* PC, Byte* higher_byte_reg, Byte* lower_byte_reg);

void LD_X_d8_Instruction(Memory* mem, Address* PC, Byte* X);

void PUSH_PC_Instruction(Memory* mem, Address* SP, Address PC);

void PUSH_XX_Instruction(Memory* mem, Address* SP, Byte higher_byte, Byte lower_byte, Address* PC);

void POP_XX_Instruction(Memory* mem, Address* SP, Byte* higher_byte, Byte* lower_byte, Address* PC);

void BIT_X_A_Instruction(Byte* F, Byte A, Address* PC, int X);

void SWAP_X_Instruction(Byte* F, Byte* X);

void SetSUBFlags(Byte* F, Byte X, Byte Y);

void ChangeBitValueFromMemory_Instruction(Memory* mem, Byte higher_byte, Byte lower_byte, bool value, int position);

}

#endif  // GAME_CPU_UTILS_H_