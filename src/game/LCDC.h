
#ifndef GAME_LCDC_H_
#define GAME_LCDC_H_

#include "primitives.h"

#define WINDOW_DISPLAY_POSITION 5
#define OBJECT_DISPLAY_POSITION 1

namespace gameboy {

bool WindowDisplayIsOn(Byte LCDC);

bool ObjectDisplayIsOn(Byte LCDC);

}

#endif  // GAME_LCDC_H_
