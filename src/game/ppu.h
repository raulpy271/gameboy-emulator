
#ifndef GAME_PPU_H_
#define GAME_PPU_H_

#include "primitives.h"
#include "hardware_definitions.h"
#include "memory.h"

namespace gameboy {

class PPU {

public:
  ColorNumber imageData[BACKGROUND_X_SIZE * BACKGROUND_Y_SIZE];
  ColorNumber screen[SCREEN_X_SIZE * SCREEN_Y_SIZE];

  void SetMemory(Memory* mem);

  void UpdateImageData();

private:

  Memory* mem;

  void ScanLine(ColorNumber* line_data, int line_number, Byte palette);

  void ReadTileLine(ColorNumber* arr_to_store, Address tile_line_address, Byte palette);

  void UpdateScreenFromBackground();

  void DrawSprites();

  void DrawSingleSprite(int y_screen, int x_screen, Byte tile_number, Byte palette);

};

}

#endif  // GAME_PPU_H_
