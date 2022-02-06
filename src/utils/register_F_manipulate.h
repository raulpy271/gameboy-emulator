
#ifndef UTILS_REGISTER_F_MANIPULATE_H_
#define UTILS_REGISTER_F_MANIPULATE_H_

#include <bitset>

#include "../game/primitives.h"

#define CARRY_FLAG_POSITION 4
#define ZERO_FLAG_POSITION 7

namespace utils {

bool carry_flag(Byte* F);

void set_carry_flag(Byte* F, bool value);

bool zero_flag(Byte* F);

void set_zero_flag(Byte* F, bool value);

}

#endif  // UTILS_REGISTER_F_MANIPULATE_H_
