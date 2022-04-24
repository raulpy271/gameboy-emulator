
#include "stdio.h"
#include <bitset>

#include "ppu.h"
#include "hardware_registers.h"
#include "hardware_definitions.h"
#include "palette.h"
#include "../utils/functions.h"

namespace gameboy {


PPU::PPU(Memory* mem) {
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

void PPU::ScanLineBackground(ColorNumber* arr_to_store_line, int background_Y_line, Byte palette) {
  ColorNumber background_line[BACKGROUND_X_SIZE];
  unsigned int tile_data_position = 0;
  unsigned int tile_reference = 0;
  unsigned int tile_line = background_Y_line % 8;
  for (int tile_number = 0; tile_number < 32; tile_number++) {
    tile_reference = mem->GetInAddr(0x9800 + (32 * utils::integer_division(background_Y_line, 8)) + tile_number);
    tile_data_position = 0x8000 + (tile_reference * 16) + (2*tile_line);
    ReadTileLine((&(background_line[0])) + (tile_number * 8), tile_data_position, palette);
  }
  const int scx = mem->GetInAddr(rSCX);
  int x_deslocated = scx;
  for (int i = 0; i < SCREEN_X_SIZE; i++) {
    arr_to_store_line[i] = background_line[x_deslocated];
    if (x_deslocated >= (BACKGROUND_X_SIZE - 1)) {
      x_deslocated = 0;
    } else {
      x_deslocated++;
    }
  }
}

Address* PPU::OAMScan(int Y_cordinate) {
  Address* sprites = new Address[MAX_SPRITES_PER_SCANLINE]{0};
  int y_screen, x_screen;
  int next_sprite_to_add = 0;
  for (Address sprite_location = OAM_START_LOCATION; sprite_location < OAM_END_LOCATION; sprite_location += 4) {
    y_screen = mem->GetInAddr(sprite_location) - 16;
    x_screen = mem->GetInAddr(sprite_location + 1) - 8;
    if (
          (Y_cordinate >= y_screen) && (Y_cordinate < (y_screen + 8)) &&
          (x_screen > (-8) && x_screen < SCREEN_X_SIZE)
        ) {
      sprites[next_sprite_to_add] = sprite_location;
      next_sprite_to_add++;
    }
  }
  return sprites;
}

void PPU::DrawSpriteLine(ColorNumber* arr_to_store_line, Address sprite_location, int Y_cordinate) {
  Byte obp;
  ColorNumber tile_line[8]; 
  ColorNumber* next_pixel_to_set;
  int y_screen = mem->GetInAddr(sprite_location) - 16;
  int x_screen = mem->GetInAddr(sprite_location + 1) - 8;
  Byte tile_number = mem->GetInAddr(sprite_location + 2);
  std::bitset<8> object_flag = std::bitset<8>(mem->GetInAddr(sprite_location + 3));
  int line_number = Y_cordinate - y_screen;
  if (object_flag[4]) {
    obp = mem->GetInAddr(rOBP1);
  } else {
    obp = mem->GetInAddr(rOBP0);
  }
  ReadTileLine(&(tile_line[0]), _VRAM8000 + (16 * tile_number) + (2 * line_number), indentity_palette);
  for (int i = 0; i < 8 && x_screen < SCREEN_X_SIZE; i++, x_screen++) {
    if (x_screen >= 0 && tile_line[i] != TRANSPARENT_COLOR) {
      next_pixel_to_set = arr_to_store_line + x_screen;
      *next_pixel_to_set = apply_palette(tile_line[i], obp);
    }
  }
}

void PPU::ScanLine(ColorNumber* arr_to_store_line, int LY, Byte palette) {
  // MODE 2
  Address* sprites = OAMScan(LY);

  // MODE 3
  const int scy = mem->GetInAddr(rSCY);
  int background_Y_line = LY + scy;
  if (background_Y_line >= (BACKGROUND_Y_SIZE)) {
    background_Y_line -= BACKGROUND_Y_SIZE;
  }
  ScanLineBackground(arr_to_store_line, background_Y_line, palette);

  for (int i = 0; i < MAX_SPRITES_PER_SCANLINE; i++) {
    if (sprites[i] != 0) {
      printf("Drawing sprite: %x\n", (unsigned int) sprites[i]);
      DrawSpriteLine(arr_to_store_line, sprites[i], LY);
    }
  }

  delete[] sprites;
}

void PPU::UpdateImageData() {
  Byte palette = mem->GetInAddr(rBGP);
  ColorNumber* image_data_pt = &(screen[0]);
  for (int LY = 0; LY < SCREEN_Y_SIZE; LY++) {
    ScanLine(image_data_pt + (SCREEN_X_SIZE * LY), LY, palette);
  }

}

}
