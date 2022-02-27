
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
  if (add >= 0xFE00 && add < 0xFEA0) {
    return MemorySegment::OAM;
  }
  if (add >= 0xFF00 && add <= 0xFFFF) {
    return MemorySegment::IO_REG_and_HRAM_and_IE;
  }
  return MemorySegment::NO_SEGMENT;
}

Byte Memory::GetInAddr(Address add) {
  switch (Memory::choose_segment(add))
  {
  case MemorySegment::CARTRIDGE_ROM:
    return cartridge_ROM[add];
  case MemorySegment::IO_REG_and_HRAM_and_IE:
    return IO_REG_and_HRAM_and_IE[add - 0xFF00];
  case MemorySegment::VRAM:
    return VRAM[add - 0x8000];
  case MemorySegment::OAM:
    return OAM[add - 0xFE00];
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
    return;
  case MemorySegment::IO_REG_and_HRAM_and_IE:
    IO_REG_and_HRAM_and_IE[add - 0xFF00] = byte_to_insert;
    return;
  case MemorySegment::VRAM:
    VRAM[add - 0x8000] = byte_to_insert;
    return;
  case MemorySegment::OAM:
    OAM[add - 0xFE00] = byte_to_insert;
    return;
  case MemorySegment::NO_SEGMENT:
    return;
  default:
    return;
  }
};

}
