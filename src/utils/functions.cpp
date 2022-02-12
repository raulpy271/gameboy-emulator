
#include "../game/primitives.h"
#include "functions.h"

namespace utils {

Address create_address_from_two_bytes(Byte higher_byte, Byte lower_byte) {
  return (higher_byte * 0x100) + lower_byte;
}

void increment_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg) {
  if (*lower_byte_reg < 0xff) {
    *lower_byte_reg = (*lower_byte_reg) + 1;
  } else {
    *lower_byte_reg = 0;
    *higher_byte_reg = (*higher_byte_reg) + 1;
  }
}

}