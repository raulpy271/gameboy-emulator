

#include <gtest/gtest.h>

#include "../src/game/primitives.h"
#include "../src/game/palette.h"

TEST(Palette, apply_palette_index0) {
  ColorNumber index0 = 0;
  Byte palette_with_index0_black = 0b00000011;

  ColorNumber black = 3;

  EXPECT_EQ(gameboy::apply_palette(index0, palette_with_index0_black), black);
}

TEST(Palette, apply_palette_index2) {
  ColorNumber index2 = 2;
  Byte palette_with_index2_dark_gray = 0b00100011;

  ColorNumber dark_gray = 2;

  EXPECT_EQ(gameboy::apply_palette(index2, palette_with_index2_dark_gray), dark_gray);
}

TEST(Palette, apply_palette_index3) {
  ColorNumber index3 = 3;
  Byte palette_with_index3_white = 0b00100011;

  ColorNumber white = 0;

  EXPECT_EQ(gameboy::apply_palette(index3, palette_with_index3_white), white);
}
