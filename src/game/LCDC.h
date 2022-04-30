
#ifndef GAME_LCDC_H_
#define GAME_LCDC_H_

#include "primitives.h"

#define WINDOW_DISPLAY_POSITION 5
#define OBJECT_DISPLAY_POSITION 1
#define BG_TILE_MAP_SELECT_POSITION 3
#define LCD_ENABLE_POSITION 7

namespace gameboy {

bool WindowDisplayIsOn(Byte LCDC);

bool ObjectDisplayIsOn(Byte LCDC);

bool BgTileMapIsOn(Byte LCDC);

bool LCDEnable(Byte LCDC);

}

#endif  // GAME_LCDC_H_
