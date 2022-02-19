
#include <bitset>
#include "ppu.h"
#include "../utils/functions.h"

namespace gameboy {


void PPU::SetMemory(Memory* mem) {
  this->mem = mem;
}

void PPU::ScanLine(ColorNumber* line_data, int line_number) {
  unsigned int tile_data_position = 0;
  unsigned int tile_reference = 0;
  unsigned int tile_line = line_number % 8;
  std::bitset<8> part_1_of_an_line;
  std::bitset<8> part_2_of_an_line;
  
  for (int tile_number = 0; tile_number < 32; tile_number++) {
    tile_reference = mem->GetInAddr(0x9800 + (32 * utils::integer_division(line_number, 8)) + tile_number);
    tile_data_position = 0x8000 + (tile_reference * 16) + (2*tile_line);
    part_1_of_an_line =  std::bitset<8>(
      (unsigned int) mem->GetInAddr(tile_data_position)
    );
    part_2_of_an_line =  std::bitset<8>(
      (unsigned int) mem->GetInAddr(tile_data_position + 1)
    );
    for (int j = 0; j < 8; j++) {
      if (part_1_of_an_line[j] && part_2_of_an_line[j]) {
        line_data[(tile_number * 8) + (8 - j)] = 0;
        continue;
      }
      if (part_1_of_an_line[j]) {
        line_data[(tile_number * 8) + (8 - j)] = 1;
        continue;
      }
      if (part_2_of_an_line[j]) {
        line_data[(tile_number * 8) + (8 - j)] = 2;
        continue;
      } else {
        line_data[(tile_number * 8) + (8 - j)] = 3;
        continue;
      }
    }


  }
}

void PPU::UpdateImageData() {
  int i;
  ColorNumber current_line_data[256];
  for (int current_line = 0; current_line < 256; current_line++) {
    ScanLine(&current_line_data[0], current_line);
    for (i = 0; i < 256; i++) {
      imageData[(current_line * 256) + i] = current_line_data[i];
    }
  }
}

}
