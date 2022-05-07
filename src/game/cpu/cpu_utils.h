
#ifndef GAME_CPU_UTILS_H_
#define GAME_CPU_UTILS_H_

#include "../primitives.h"
#include "../memory.h"

namespace gameboy {

void INC_X_Instruction(Byte* X, Byte* F, Address* PC);

void DEC_X_Instruction(Byte* X, Byte* F, Address* PC);

void ADD_X_Y_Instruction(Byte* X, Byte* Y, Byte* F);

void AND_X_Y_Instruction(Byte* X, Byte* Y, Byte* F, Address* PC);

void LD_XX_d16_Instruction(Memory* mem, Address* PC, Byte* higher_byte_reg, Byte* lower_byte_reg);

void LD_X_d8_Instruction(Memory* mem, Address* PC, Byte* X);

void PUSH_PC_Instruction(Memory* mem, Address* SP, Address PC);

void PUSH_XX_Instruction(Memory* mem, Address* SP, Byte higher_byte, Byte lower_byte, Address* PC);

void POP_XX_Instruction(Memory* mem, Address* SP, Byte* higher_byte, Byte* lower_byte, Address* PC);

void BIT_X_A_Instruction(Byte* F, Byte A, Address* PC, int X);

void ChangeBitValueFromMemory_Instruction(Memory* mem, Byte higher_byte, Byte lower_byte, bool value, int position);

}

#endif  // GAME_CPU_UTILS_H_