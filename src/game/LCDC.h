
#ifndef GAME_LCDC_H_
#define GAME_LCDC_H_

#include "primitives.h"

#define BG_WINDOW_DISPLAY_POSITION 0
#define OBJECT_DISPLAY_POSITION 1
#define BG_TILE_MAP_SELECT_POSITION 3
#define BG_WINDOW_TILE_DATA_AREA 4
#define WINDOW_DISPLAY_POSITION 5
#define WINDOW_TILE_MAP_SELECT_POSITION 6
#define LCD_ENABLE_POSITION 7

namespace gameboy {

bool BGWindowDisplayIsOn(Byte LCDC);

bool WindowDisplayIsOn(Byte LCDC);

bool ObjectDisplayIsOn(Byte LCDC);

bool BgTileMapIsOn(Byte LCDC);

bool WindowTileMapIsOn(Byte LCDC);

bool LCDEnable(Byte LCDC);

bool TileDataArea8000(Byte LCDC);

}

#endif  // GAME_LCDC_H_
