

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

TEST(ArithmeticInstructions, AND_A_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, AND_A_C);
  game.cpu.reg.A = 0b11000100;
  game.cpu.reg.C = 0b10100100;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b10000100);
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

TEST(ArithmeticInstructions, ADD_A_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_A_A);
  game.mem.SetInAddr(0x101, ADD_A_A);
  game.cpu.reg.A = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x20 * 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);

  game.cpu.reg.A = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A,0);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
}

TEST(ArithmeticInstructions, ADD_A_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_A_B);
  game.mem.SetInAddr(0x101, ADD_A_B);
  game.cpu.reg.A = 0x20;
  game.cpu.reg.B = 0xa0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0xc0);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);

  game.cpu.reg.A = 0x0;
  game.cpu.reg.B = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
}

TEST(ArithmeticInstructions, ADD_A_B_instruction_carry_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_A_B);
  game.mem.SetInAddr(0x101, ADD_A_B);
  game.cpu.reg.A = 0xf0;
  game.cpu.reg.B = 0xc0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), true);

  game.cpu.reg.A = 0xf0;
  game.cpu.reg.B = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0xf1);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, ADD_A_B_instruction_half_carry_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_A_B);
  game.mem.SetInAddr(0x101, ADD_A_B);
  game.cpu.reg.A = 0xf0;
  game.cpu.reg.B = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);

  game.cpu.reg.A = 0x0a;
  game.cpu.reg.B = 0x0b;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x15);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, ADD_A_d8_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_A_d8);
  game.mem.SetInAddr(0x101, 0x5);
  game.cpu.reg.A = 0x0f;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x14);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
}

TEST(ArithmeticInstructions, SUB_A_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, SUB_A_B);
  game.cpu.reg.A = 0x9;
  game.cpu.reg.B = 0x5;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x9 - 0x5);
  EXPECT_EQ(game.cpu.reg.B, 0x5);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);
}

TEST(ArithmeticInstructions, SUB_A_B_instruction_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, SUB_A_B);
  game.mem.SetInAddr(0x101, SUB_A_B);
  game.cpu.reg.A = 0x8;
  game.cpu.reg.B = 0x4;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x4);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, SUB_A_B_instruction_carry_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, SUB_A_B);
  game.mem.SetInAddr(0x101, SUB_A_B);
  game.cpu.reg.A = 0x8;
  game.cpu.reg.B = 0x5;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x3);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, SUB_A_B_instruction_half_carry_flag) {
  gameboy::Console game;
  Byte expected_result;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, SUB_A_B);
  game.mem.SetInAddr(0x101, SUB_A_B);
  game.cpu.reg.A = 0b00001000;
  game.cpu.reg.B = 0b00000100;
  expected_result = game.cpu.reg.A - game.cpu.reg.B;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, expected_result);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);

  game.cpu.reg.A = 0b00000100;
  game.cpu.reg.B = 0b00001000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(ArithmeticInstructions, ADD_HL_BC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_HL_BC);
  game.cpu.reg.H = 0x20;
  game.cpu.reg.L = 0x01;

  game.cpu.reg.B = 0x10;
  game.cpu.reg.C = 0xa0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x30);
  EXPECT_EQ(game.cpu.reg.L, 0xa1);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.reg.PC = 0x100;
  game.cpu.reg.H = 0x20;
  game.cpu.reg.L = 0x02;
  game.cpu.reg.B = 0x10;
  game.cpu.reg.C = 0xff;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x31);
  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, ADD_HL_BC_instruction_overflow) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_HL_BC);
  game.cpu.reg.H = 0xff;
  game.cpu.reg.L = 0x01;

  game.cpu.reg.B = 0x10;
  game.cpu.reg.C = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0b00001111);
  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, ADD_HL_BC_instruction_half_carry) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_HL_BC);
  game.cpu.reg.H = 0x0f;
  game.cpu.reg.L = 0x00;

  game.cpu.reg.B = 0x12;
  game.cpu.reg.C = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x21);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, ADD_HL_DE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_HL_DE);
  game.cpu.reg.H = 0x20;
  game.cpu.reg.L = 0x01;

  game.cpu.reg.D = 0x10;
  game.cpu.reg.E = 0xa0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x30);
  EXPECT_EQ(game.cpu.reg.L, 0xa1);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(ArithmeticInstructions, ADD_HL_DE_instruction_half_carry) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, ADD_HL_DE);
  game.cpu.reg.H = 0x0f;
  game.cpu.reg.L = 0x00;

  game.cpu.reg.D = 0x12;
  game.cpu.reg.E = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x21);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}
