
#include <bitset>
#include <math.h>

#include "../game/primitives.h"
#include "functions.h"

namespace utils {

Address create_address_from_two_bytes(Byte higher_byte, Byte lower_byte) {
  return (higher_byte * 0x100) + lower_byte;
}

std::pair<Byte, Byte> create_two_bytes_from_address(Address addr) {
  std::bitset<16> addr_bitset(addr);
  std::pair<Byte, Byte> two_bytes;
  Byte higher_byte = 0;
  Byte lower_byte = 0;
  for (int i = 0; i < 8; i++) {
    if (addr_bitset[i]) {
      lower_byte += pow(2, i);
    }
  }
  for (int i = 0; i < 8; i++) {
    if (addr_bitset[8 + i]) {
      higher_byte += pow(2, i);
    }
  }
  two_bytes.first = higher_byte;
  two_bytes.second = lower_byte;
  return two_bytes;
}

void increment_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg) {
  if (*lower_byte_reg < 0xff) {
    *lower_byte_reg = (*lower_byte_reg) + 1;
  } else {
    *lower_byte_reg = 0;
    *higher_byte_reg = (*higher_byte_reg) + 1;
  }
}

void decrement_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg) {
  if ((*lower_byte_reg) > 0) {
    (*lower_byte_reg) = (*lower_byte_reg) - 1;
  } else if ((*higher_byte_reg) > 0) {
    (*higher_byte_reg) = (*higher_byte_reg) - 1;
    (*lower_byte_reg) = 0xff;
  }
}

unsigned int integer_division(unsigned int n, unsigned int d) {
  return (unsigned int)(n - (n % d))/d;
}

}