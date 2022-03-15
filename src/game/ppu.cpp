
#include <bitset>

#include "ppu.h"
#include "hardware_registers.h"
#include "hardware_definitions.h"
#include "palette.h"
#include "../utils/functions.h"

namespace gameboy {


void PPU::SetMemory(Memory* mem) {
  this->mem = mem;
}

void PPU::ReadTileLine(ColorNumber* arr_to_store, Address tile_line_address, Byte palette) {
  std::bitset<8> part_1_of_an_line;
  std::bitset<8> part_2_of_an_line;
  part_1_of_an_line =  std::bitset<8>(
    (unsigned int) mem->GetInAddr(tile_line_address)
  );
  part_2_of_an_line =  std::bitset<8>(
    (unsigned int) mem->GetInAddr(tile_line_address + 1)
  );
  for (int j = 0; j < 8; j++) {
    if (part_1_of_an_line[j] && part_2_of_an_line[j]) {
      arr_to_store[7 - j] = apply_palette(3, palette);
      continue;
    }
    if (part_1_of_an_line[j]) {
      arr_to_store[(7 - j)] = apply_palette(1, palette);
      continue;
    }
    if (part_2_of_an_line[j]) {
      arr_to_store[(7 - j)] = apply_palette(2, palette);
      continue;
    } else {
      arr_to_store[(7 - j)] = apply_palette(0, palette);
      continue;
    }
  }
}

void PPU::ScanLine(ColorNumber* arr_to_store_line, int background_Y_line, Byte palette) {
  unsigned int tile_data_position = 0;
  unsigned int tile_reference = 0;
  unsigned int tile_line = background_Y_line % 8;
  for (int tile_number = 0; tile_number < 32; tile_number++) {
    tile_reference = mem->GetInAddr(0x9800 + (32 * utils::integer_division(background_Y_line, 8)) + tile_number);
    tile_data_position = 0x8000 + (tile_reference * 16) + (2*tile_line);
    ReadTileLine(arr_to_store_line + (tile_number * 8), tile_data_position, palette);
  }
}

void PPU::DrawSingleSprite(int y_screen, int x_screen, Byte tile_number, Byte palette) {
  int x, y;
  int tile_line_address;
  ColorNumber tile_line[8];
  int tile_line_number = 0;
  int tile_column_number = 0;
  for (y = y_screen; y < (y_screen + 8); y++, tile_line_number++) {
    if (y < 0 || y >= SCREEN_Y_SIZE) {
      continue;
    }
    tile_line_address = _VRAM8000 + (tile_number * 16) + (2*tile_line_number);
    ReadTileLine(tile_line, tile_line_address, indentity_palette);
    for (x = x_screen, tile_column_number = 0; x < (x_screen + 8); x++, tile_column_number++) {
      if (x < 0 || x >= SCREEN_X_SIZE) {
        continue;
      }
      if (tile_line[tile_column_number]) {
        screen[(SCREEN_X_SIZE * y) + x] =  apply_palette(tile_line[tile_column_number], palette);
      }
    }
  }
}

void PPU::DrawSprites() {
  int x_screen, y_screen;
  std::bitset<8> object_flag;
  Byte tile_number; 
  Byte obp;
  for (int sprite_location = OAM_START_LOCATION; sprite_location <= OAM_END_LOCATION; sprite_location += 4) {
    y_screen = mem->GetInAddr(sprite_location) - 16;
    x_screen = mem->GetInAddr(sprite_location + 1) - 8;
    tile_number = mem->GetInAddr(sprite_location + 2);
    object_flag = std::bitset<8>(mem->GetInAddr(sprite_location + 3));
    if (object_flag[4]) {
      obp = mem->GetInAddr(rOBP1);
    } else {
      obp = mem->GetInAddr(rOBP0);
    }
    DrawSingleSprite(y_screen, x_screen, tile_number, obp);
  }
}

void PPU::UpdateScreenFromBackground() {
  int x;
  int y;
  int x_deslocated;
  int y_deslocated;
  const int scx = mem->GetInAddr(rSCX);
  const int scy = mem->GetInAddr(rSCY);
  for (y = 0, y_deslocated = scy; y < SCREEN_Y_SIZE; y++) {
    for (x = 0, x_deslocated = scx; x < SCREEN_X_SIZE; x++) {
      screen[(SCREEN_X_SIZE * y) + x] = imageData[(BACKGROUND_X_SIZE * y_deslocated) + x_deslocated];
      if (x_deslocated >= (BACKGROUND_X_SIZE - 1)) {
        x_deslocated = 0;
      } else {
        x_deslocated++;
      }
    }
    if (y_deslocated >= (BACKGROUND_Y_SIZE - 1)) {
      y_deslocated = 0;
    } else {
      y_deslocated++;
    }
  }
}

void PPU::UpdateImageData() {
  Byte palette = mem->GetInAddr(rBGP);
  ColorNumber* image_data_pt = &(imageData[0]);
  for (int current_line = 0; current_line < 256; current_line++) {
    ScanLine(image_data_pt + (256 * current_line), current_line, palette);
  }
  UpdateScreenFromBackground();
  DrawSprites();
}

}
