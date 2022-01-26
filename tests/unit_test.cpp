
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/opcodes.h"

TEST(Instructions, JP_a16_instruction) {
  gameboy::Console game;
  game.mem.SetInAddr(0x100, JP_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.reg.PC = 0x100;
  game.cpu.execute_intruction(game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, LD_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.mem.SetInAddr(0x100, LD_d8);
  game.mem.SetInAddr(0x101, to_load);
  game.cpu.reg.PC = 0x100;
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(game.mem);

  EXPECT_EQ(game.cpu.reg.A, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

