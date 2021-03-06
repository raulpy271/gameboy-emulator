
#include "register_F_manipulate.h"

namespace utils {

bool carry_flag(Byte* F) {
  std::bitset<8> f_bitset(*F);
  return (bool) f_bitset[CARRY_FLAG_POSITION];
}

bool subtract_flag(Byte* F) {
  std::bitset<8> f_bitset(*F);
  return (bool) f_bitset[SUBTRACT_FLAG_POSITION];
}

bool half_carry_flag(Byte* F) {
  std::bitset<8> f_bitset(*F);
  return (bool) f_bitset[HALF_CARRY_FLAG_POSITION];
}

void set_subtract_flag(Byte* F, bool value) {
  std::bitset<8> f_bitset(*F);
  f_bitset.set(SUBTRACT_FLAG_POSITION, value);
  *F = (Byte) f_bitset.to_ulong();
}

void set_carry_flag(Byte* F, bool value) {
  std::bitset<8> f_bitset(*F);
  f_bitset.set(CARRY_FLAG_POSITION, value);
  *F = (Byte) f_bitset.to_ulong();
}

bool zero_flag(Byte* F) {
  std::bitset<8> f_bitset(*F);
  return (bool) f_bitset[ZERO_FLAG_POSITION];
}

void set_half_carry_flag(Byte* F, bool value) {
  std::bitset<8> f_bitset(*F);
  f_bitset.set(HALF_CARRY_FLAG_POSITION, value);
  *F = (Byte) f_bitset.to_ulong();
}

void set_zero_flag(Byte* F, bool value) {
  std::bitset<8> f_bitset(*F);
  f_bitset.set(ZERO_FLAG_POSITION, value);
  *F = (Byte) f_bitset.to_ulong();
}

}