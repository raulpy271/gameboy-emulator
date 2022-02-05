
#include <bitset>

#include "tile.h"

namespace gameboy {

Tile::~Tile() {
  delete this;
}

Tile* Tile::create_tile(Byte* first_byte) {

  int line_count = 0;
  std::bitset<8> part_1_of_an_line;
  std::bitset<8> part_2_of_an_line;
  Tile* tile = new Tile();
  
  for (int i = 0; i < 15; i += 2) {
    part_1_of_an_line =  std::bitset<8>((unsigned int)first_byte[i]);
    part_2_of_an_line =  std::bitset<8>((unsigned int)first_byte[i + 1]);
    for (int j = 0; j < 8; j++) {
      if (part_1_of_an_line[j] && part_2_of_an_line[j]) {
        tile->data[(line_count * 8) + j] = 3;
        continue;
      }
      if (part_1_of_an_line[j]) {
        tile->data[(line_count * 8) + j] = 1;
        continue;
      }
      if (part_2_of_an_line[j]) {
        tile->data[(line_count * 8) + j] = 2;
        continue;
      } else {
        tile->data[(line_count * 8) + j] = 0;
        continue;
      }
    }
  line_count++;
  }
  return tile;
}

}