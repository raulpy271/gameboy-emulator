
#include "memory.h"

namespace gameboy {

Byte Memory::GetInAddr(Address add) {
  if (add < (32 * KB)) {
    return cartridge[add];
  }
  return 0x0;
};

void Memory::SetInAddr(Address add, Byte byte_to_insert) {
  if (add < (32 * KB)) {
    cartridge[add] = byte_to_insert;
  }
};

}
