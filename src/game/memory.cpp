
#include "memory.h"

namespace gameboy {

MemorySegment Memory::choose_segment(Address add) {
  if (add < 0x8000) {
    return MemorySegment::CARTRIDGE_ROM;
  }
  if (add < 0xA000) {
    return MemorySegment::VRAM;
  }
  if (add < 0xC000) {
    return MemorySegment::CARTRIDGE_RAM;
  }
  if (add < 0xD000) {
    return MemorySegment::WRAM_0;
  }
  if (add < 0xE000) {
    return MemorySegment::WRAM_N;
  }
  return MemorySegment::NO_SEGMENT;
}

Byte Memory::GetInAddr(Address add) {
  switch (Memory::choose_segment(add))
  {
  case MemorySegment::CARTRIDGE_ROM:
    return cartridge_ROM[add];
  case MemorySegment::NO_SEGMENT:
    return 0xff;
  default:
    return 0xff;
  }
};

void Memory::SetInAddr(Address add, Byte byte_to_insert) {
  switch (Memory::choose_segment(add))
  {
  case MemorySegment::CARTRIDGE_ROM:
    cartridge_ROM[add] = byte_to_insert;
  case MemorySegment::NO_SEGMENT:
    return;
  default:
    return;
  }
};

}
