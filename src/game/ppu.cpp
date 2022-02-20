
#include <bitset>
#include "ppu.h"
#include "../utils/functions.h"

namespace gameboy {


void PPU::SetMemory(Memory* mem) {
  this->mem = mem;
}

void PPU::ReadTileLine(ColorNumber* arr_to_store, Address tile_line_address) {
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
      arr_to_store[8 - j] = 0;
      continue;
    }
    if (part_1_of_an_line[j]) {
      arr_to_store[(8 - j)] = 1;
      continue;
    }
    if (part_2_of_an_line[j]) {
      arr_to_store[(8 - j)] = 2;
      continue;
    } else {
      arr_to_store[(8 - j)] = 3;
      continue;
    }
  }
}

void PPU::ScanLine(ColorNumber* arr_to_store_line, int background_Y_line) {
  unsigned int tile_data_position = 0;
  unsigned int tile_reference = 0;
  unsigned int tile_line = background_Y_line % 8;
  for (int tile_number = 0; tile_number < 32; tile_number++) {
    tile_reference = mem->GetInAddr(0x9800 + (32 * utils::integer_division(background_Y_line, 8)) + tile_number);
    tile_data_position = 0x8000 + (tile_reference * 16) + (2*tile_line);
    ReadTileLine(arr_to_store_line + (tile_number * 8), tile_data_position);
  }
}

void PPU::UpdateImageData() {
  ColorNumber* image_data_pt = &(imageData[0]);
  for (int current_line = 0; current_line < 256; current_line++) {
    ScanLine(image_data_pt + (256 * current_line), current_line);
  }
}

}
