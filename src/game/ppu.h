
#ifndef GAME_PPU_H_
#define GAME_PPU_H_

#include "primitives.h"
#include "memory.h"

namespace gameboy {

class PPU {

public:
  ColorNumber imageData[256 * 256];

  const unsigned int imageSize = 256 * 256;
  
  void SetMemory(Memory* mem);

  void UpdateImageData();

private:

  Memory* mem = 0x0;

  void ScanLine(ColorNumber* line_data, int line_number);

  bool black;
};

}

#endif  // GAME_PPU_H_
