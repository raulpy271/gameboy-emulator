
#ifndef GAME_MEMORY_H_
#define GAME_MEMORY_H_

#include "primitives.h"

namespace gameboy {

enum class MemorySegment {
  CARTRIDGE_ROM,
  VRAM,
  CARTRIDGE_RAM,
  WRAM_0,
  WRAM_N,
  OAM,
  IO_REG_and_HRAM_and_IE,
  NO_SEGMENT
};

class Memory {
 public:
  Byte GetInAddr(Address add);

  void SetInAddr(Address add, Byte byte_to_insert);

  void IncrementDivRegister();

  static MemorySegment choose_segment(Address add);

 private:
  Byte          cartridge_ROM[0x8000 - 0x0000] = {0x0};
  Byte                   VRAM[0xA000 - 0x8000] = {0x0};
  Byte          cartridge_RAM[0xC000 - 0xA000] = {0x0};
  Byte                 WRAM_0[0xD000 - 0xC000] = {0x0};
  Byte                 WRAM_N[0xE000 - 0xD000] = {0x0};
  Byte                    OAM[0xFEA0 - 0xFE00] = {0x0};
  Byte IO_REG_and_HRAM_and_IE[0xFFFF - 0xFF00] = {0x0};

};

}

#endif  // GAME_MEMORY_H_