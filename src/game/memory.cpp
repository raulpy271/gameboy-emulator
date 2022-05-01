
#include <bitset>
#include <iostream>

#include "memory.h"
#include "STAT.h"
#include "hardware_registers.h"
#include "hardware_definitions.h"

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
  if (add == rP1) {
    return keypad.ReadOnP1Register(IO_REG_and_HRAM_and_IE[add - 0xFF00]);
  }
  switch (Memory::choose_segment(add))
  {
  case MemorySegment::CARTRIDGE_ROM:
    return cartridge_ROM[add];
  case MemorySegment::CARTRIDGE_RAM:
    return cartridge_RAM[add - 0xA000];
  case MemorySegment::IO_REG_and_HRAM_and_IE:
    return IO_REG_and_HRAM_and_IE[add - 0xFF00];
  case MemorySegment::VRAM:
    return VRAM[add - 0x8000];
  case MemorySegment::WRAM_0:
    return WRAM_0[add - 0xC000];
  case MemorySegment::WRAM_N:
    return WRAM_N[add - 0xD000];
  case MemorySegment::OAM:
    return OAM[add - 0xFE00];
  case MemorySegment::NO_SEGMENT:
    std::cout << "Acessing in a nonmapped address: " << (unsigned int) add << std::endl;
    return 0xff;
  default:
    std::cout << "Acessing in a nonmapped address: " << (unsigned int) add << std::endl;
    return 0xff;
  }
};

void Memory::SetInAddr(Address add, Byte byte_to_insert) {
  if (add == rP1) {
    IO_REG_and_HRAM_and_IE[add - 0xFF00] = keypad.WriteOnP1Register(byte_to_insert);
    return;
  }
  if (add == rDMA) {
    executeDMATransfer(byte_to_insert);
    return;
  }
  if (add == rSTAT) {
    IO_REG_and_HRAM_and_IE[add - 0xFF00] = GetByteToWriteInSTAT(byte_to_insert, IO_REG_and_HRAM_and_IE[add - 0xFF00]);
    return;
  }
  switch (Memory::choose_segment(add))
  {
  case MemorySegment::CARTRIDGE_ROM:
    cartridge_ROM[add] = byte_to_insert;
    return;
  case MemorySegment::CARTRIDGE_RAM:
    cartridge_RAM[add - 0xA000] = byte_to_insert;
    return;
  case MemorySegment::IO_REG_and_HRAM_and_IE:
    IO_REG_and_HRAM_and_IE[add - 0xFF00] = byte_to_insert;
    return;
  case MemorySegment::VRAM:
    VRAM[add - 0x8000] = byte_to_insert;
    return;
  case MemorySegment::WRAM_0:
    WRAM_0[add - 0xC000] = byte_to_insert;
    return;
  case MemorySegment::WRAM_N:
    WRAM_N[add - 0xD000] = byte_to_insert;
    return;
  case MemorySegment::OAM:
    OAM[add - 0xFE00] = byte_to_insert;
    return;
  case MemorySegment::NO_SEGMENT:
    std::cout << "Setting in a nonmapped address: " << (unsigned int) add << std::endl;
    return;
  default:
    std::cout << "Setting in a nonmapped address: " << (unsigned int) add << std::endl;
    return;
  }
};

void Memory::IncrementDivRegister() {
  Byte div_value = GetInAddr(rDIV);
  if (div_value == 0xff) {
    IO_REG_and_HRAM_and_IE[rDIV - 0xFF00] = 0;
  } else {
    IO_REG_and_HRAM_and_IE[rDIV - 0xFF00] = div_value + 1;
  }
};

void Memory::SetCoincidenceFlagLYEqualLYC(bool value) {
  std::bitset<8> STAT_bitset(GetInAddr(rSTAT));
  STAT_bitset[COINCIDENCE_FLAG_POSITION] = value;
  IO_REG_and_HRAM_and_IE[rSTAT - 0xFF00] = STAT_bitset.to_ulong();
}

void Memory::executeDMATransfer(Byte source_destination_high_byte) {
  Address source = source_destination_high_byte * 0x100;
  Byte value;
  for (Address destination = OAM_START_LOCATION; destination <= OAM_END_LOCATION; destination++, source++) {
    value = GetInAddr(source);
    SetInAddr(destination, value);
  }
}

}
