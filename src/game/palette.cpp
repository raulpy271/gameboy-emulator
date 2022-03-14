
#include <bitset>

#include "palette.h"

namespace gameboy {

ColorNumber apply_palette(ColorNumber color, Byte palette) {
  std::bitset<8> palette_bitset(palette);
  int lower_bit  = (int) palette_bitset[(2*color)];
  int higher_bit = (int) palette_bitset[(2*color) + 1];
  return (higher_bit * 2) + lower_bit;
}

}
