
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

  Memory* mem;

  void ScanLine(ColorNumber* line_data, int line_number);

  void ReadTileLine(ColorNumber* arr_to_store, Address tile_line_address);

};

}

#endif  // GAME_PPU_H_
