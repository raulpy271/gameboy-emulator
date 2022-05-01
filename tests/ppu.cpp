
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/ppu.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"


TEST(PPU, LY_register) {
  gameboy::Console game;

  EXPECT_EQ(game.mem.GetInAddr(rLY), 0);

  game.ppu.ScanLine();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 1);

  game.ppu.ScanLine();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 2);
}

TEST(PPU, GetTileAddressMode8000) {
  gameboy::Memory mem;
  gameboy::PPU ppu(&mem);
  Byte mode8000 = 1 << 4;

  mem.SetInAddr(rLCDC, mode8000);

  EXPECT_EQ(ppu.GetTileAddress(0), 0x8000);
  EXPECT_EQ(ppu.GetTileAddress(127), 0x8000 + (16 * 127));
  EXPECT_EQ(ppu.GetTileAddress(128), 0x8800);
}

TEST(PPU, GetTileAddressMode8800) {
  gameboy::Memory mem;
  gameboy::PPU ppu(&mem);
  Byte mode8800 = 0 << 4;

  mem.SetInAddr(rLCDC, mode8800);

  EXPECT_EQ(ppu.GetTileAddress(0), 0x9000);
  EXPECT_EQ(ppu.GetTileAddress(127), 0x9000 + (16 * 127));
  EXPECT_EQ(ppu.GetTileAddress(128), 0x8800);
}

TEST(PPU, LYC_equal_LY_flag) {
  gameboy::Console game;
  Byte lyc_enqual_ly = 1 << 2;
  game.initialize_registers();
  game.mem.SetInAddr(rLYC, 2);
  game.mem.SetInAddr(rSTAT, 0);

  game.ScanLineAndSTATInterruptions();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 1);
  EXPECT_EQ(game.mem.GetInAddr(rSTAT) && lyc_enqual_ly, false);

  game.ScanLineAndSTATInterruptions();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 2);
  EXPECT_EQ(game.mem.GetInAddr(rSTAT) && lyc_enqual_ly, false);

  game.ScanLineAndSTATInterruptions();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 3);
  EXPECT_EQ(game.mem.GetInAddr(rSTAT) && lyc_enqual_ly, true);

  game.ScanLineAndSTATInterruptions();

  EXPECT_EQ(game.mem.GetInAddr(rLY), 4);
  EXPECT_EQ(game.mem.GetInAddr(rSTAT) && lyc_enqual_ly, false);
}