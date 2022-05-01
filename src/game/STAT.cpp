
#include <bitset>

#include "STAT.h"


namespace gameboy {

Byte GetByteToWriteInSTAT(Byte byte_to_write, Byte old_byte) {
  return (old_byte & 0b00000111) | (byte_to_write & 0b11111000);
}

}
