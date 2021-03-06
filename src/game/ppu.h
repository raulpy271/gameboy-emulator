
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

  PPU(Memory* mem);

  void ScanLine();

  Address GetTileAddress(Byte tile_index);

private:

  Memory* mem;

  void ScanLineBackground(ColorNumber* arr_to_store_line, int background_Y_line, Byte palette);

  void ScanLineWindow(ColorNumber* arr_to_store_line, int background_Y_line, Byte palette);

  void DrawSpriteLine(ColorNumber* arr_to_store_line, Address sprite_location, int Y_cordinate);

  Address* OAMScan(int Y_cordinate);

  void ReadTileLine(ColorNumber* arr_to_store, Address tile_line_address, Byte palette);


  Address GetBGTileMapAddress();

  Address GetWindowTileMapAddress();

};

}

#endif  // GAME_PPU_H_
