
#ifndef GAME_CPU_UTILS_H_
#define GAME_CPU_UTILS_H_

#include "../primitives.h"
#include "../memory.h"

namespace gameboy {

void LD_XX_d16_Instruction(Memory* mem, Address* PC, Byte* higher_byte_reg, Byte* lower_byte_reg);

void LD_X_d8_Instruction(Memory* mem, Address* PC, Byte* X);

void ChangeBitValueFromMemory_Instruction(Memory* mem, Byte higher_byte, Byte lower_byte, bool value, int position);

}

#endif  // GAME_CPU_UTILS_H_