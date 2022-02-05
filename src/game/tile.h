
#ifndef GAME_TILE_H_
#define GAME_TILE_H_

#include "primitives.h"

namespace gameboy {

class Tile {
public:
  ColorNumber data[8 * 8];

  ~Tile();

  static Tile* create_tile(Byte* first_byte);
};

}

#endif  // GAME_TILE_H_