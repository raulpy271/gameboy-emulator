
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"

TEST(InitializeRegisters, check_PC_and_SP_value) {
  gameboy::Console game;
  game.initialize_registers();

  EXPECT_EQ(game.cpu.reg.PC, 0x100);
  EXPECT_EQ(game.cpu.reg.SP, 0xFFFE);
  EXPECT_EQ(
    game.mem.GetInAddr(rBGP),
    0xFC
  );
}

TEST(InitializeRegisters, hardware_registers) {
  gameboy::Console game;
  game.initialize_registers();

  EXPECT_EQ(game.mem.GetInAddr(rBGP), 0xFC);
  EXPECT_EQ(game.mem.GetInAddr(rIF), 0xE1);
  EXPECT_EQ(game.mem.GetInAddr(rLCDC), 0x91);
}