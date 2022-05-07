

#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/cpu/opcodes.h"
#include "../src/utils/register_F_manipulate.h"

TEST(ArithmeticInstructions, XOR_A_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, XOR_A_C);
  game.cpu.reg.A = 0b11100101;
  game.cpu.reg.C = 0b11010100;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b00110001);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, XOR_A_C_instruction_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, XOR_A_C);
  game.cpu.reg.A = 0xf0;
  game.cpu.reg.C = 0xf0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, XOR_A_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, XOR_A_A);
  game.cpu.reg.A = 0b00000100;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(game.cpu.reg.F, 0b10000000);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, OR_A_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OR_A_C);
  game.cpu.reg.A = 0b00000100;
  game.cpu.reg.C = 0b01000101;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b01000101);
  EXPECT_EQ(game.cpu.reg.F, 0x0);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, OR_A_C_instruction_affect_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OR_A_C);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.C = 0x0;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, OR_A_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OR_A_B);
  game.cpu.reg.A = 0b00000100;
  game.cpu.reg.B = 0b01000101;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b01000101);
  EXPECT_EQ(game.cpu.reg.F, 0x0);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, OR_A_B_instruction_affect_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OR_A_B);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.B = 0x0;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, AND_A_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, AND_A_A);
  game.cpu.reg.A = 0b00000100;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b00000100);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, AND_A_d8_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, AND_A_d8);
  game.mem.SetInAddr(0x101, 0b10111010);
  game.cpu.reg.A = 0b00100111;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b00100010);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, AND_A_d8_instruction_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, AND_A_d8);
  game.mem.SetInAddr(0x101, 0b11110000);
  game.cpu.reg.A = 0b00001111;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}
