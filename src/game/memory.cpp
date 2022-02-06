
#include "memory.h"

namespace gameboy {

MemorySegment Memory::choose_segment(Address add) {
  if (add < 0x8000) {
    return MemorySegment::CARTRIDGE_ROM;
  }
  if (add < 0xA000) {
    return MemorySegment::VRAM;
  }
  return MemorySegment::NO_SEGMENT;
}

Byte Memory::GetInAddr(Address add) {
  if (add < (32 * 1024)) {
    return cartridge_ROM[add];
  }
  return 0x0;
};

void Memory::SetInAddr(Address add, Byte byte_to_insert) {
  if (add < (32 * 1024)) {
    cartridge_ROM[add] = byte_to_insert;
  }
};

}
