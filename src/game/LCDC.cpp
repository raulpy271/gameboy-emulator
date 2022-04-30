
#include <bitset>

#include "LCDC.h"


namespace gameboy {

bool BGWindowDisplayIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[BG_WINDOW_DISPLAY_POSITION];
}

bool WindowDisplayIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[WINDOW_DISPLAY_POSITION];
}

bool ObjectDisplayIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[OBJECT_DISPLAY_POSITION];
}

bool BgTileMapIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[BG_TILE_MAP_SELECT_POSITION];
}

bool WindowTileMapIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[WINDOW_TILE_MAP_SELECT_POSITION];
}

bool LCDEnable(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[LCD_ENABLE_POSITION];
}

bool TileDataArea8000(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[BG_WINDOW_TILE_DATA_AREA];
}

}
