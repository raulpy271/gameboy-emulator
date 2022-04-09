
#ifndef UTILS_REGISTER_F_MANIPULATE_H_
#define UTILS_REGISTER_F_MANIPULATE_H_

#include <bitset>

#include "../game/primitives.h"

#define CARRY_FLAG_POSITION 4
#define SUBTRACT_FLAG_POSITION 6
#define ZERO_FLAG_POSITION 7
#define HALF_CARRY_FLAG_POSITION 5

namespace utils {

bool carry_flag(Byte* F);

bool subtract_flag(Byte* F);

bool half_carry_flag(Byte* F);

void set_half_carry_flag(Byte* F, bool value);

void set_subtract_flag(Byte* F, bool value);

void set_carry_flag(Byte* F, bool value);

bool zero_flag(Byte* F);

void set_zero_flag(Byte* F, bool value);

}

#endif  // UTILS_REGISTER_F_MANIPULATE_H_
