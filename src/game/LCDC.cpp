
#include <bitset>

#include "LCDC.h"


namespace gameboy {

bool WindowDisplayIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[WINDOW_DISPLAY_POSITION];
}

bool ObjectDisplayIsOn(Byte LCDC) {
  std::bitset<8> LCDC_bitset(LCDC);
  return LCDC_bitset[OBJECT_DISPLAY_POSITION];
}

}

