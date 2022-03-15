
#ifndef GAME_PALETTE_H_
#define GAME_PALETTE_H_

#include "primitives.h"

namespace gameboy {

// This palette don't change the color index, because index 0 is mapped to 0. Index 1 is mapped to 1 and so on.
const Byte indentity_palette = 0b11100100; 

ColorNumber apply_palette(ColorNumber color, Byte palette);


}

#endif  // GAME_PALETTE_H_