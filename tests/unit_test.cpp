
#include <gtest/gtest.h>

#include "../src/game/game.h"

TEST(Instructions, JP_a16_instruction) {
  gameboy::Console game;
  game.mem.SetInAddr(0x100, 0xc3);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.reg.PC = 0x100;
  game.cpu.execute_intruction(game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}
