
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/cpu/cb_prefixed_opcodes.h"
#include "../src/utils/register_F_manipulate.h"

TEST(PrefixedInstructions, BIT_0_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, BIT_0_A);
  game.mem.SetInAddr(0x102, OPCODE_PREFIX);
  game.mem.SetInAddr(0x103, BIT_0_A);
  game.cpu.reg.A = 0b00000000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.F, 0b10100000);

  game.cpu.reg.A = 0b00000001;
  game.cpu.reg.F = 0b00010000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x104);
  EXPECT_EQ(game.cpu.reg.F, 0b00110000);
}

TEST(PrefixedInstructions, BIT_1_A_instruction_bit_1_is_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, BIT_1_A);
  game.cpu.reg.A = 0b00000000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.F, 0b10100000);
}

TEST(PrefixedInstructions, BIT_1_A_instruction_bit_1_is_one) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, BIT_1_A);
  game.cpu.reg.A = 0b00000010;
  game.cpu.reg.F = 0b00010000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.F, 0b00110000);
}

TEST(PrefixedInstructions, BIT_2_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, BIT_2_A);
  game.mem.SetInAddr(0x102, OPCODE_PREFIX);
  game.mem.SetInAddr(0x103, BIT_2_A);
  game.cpu.reg.A = 0b00000000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.F, 0b10100000);

  game.cpu.reg.A = 0b00000100;
  game.cpu.reg.F = 0b00010000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x104);
  EXPECT_EQ(game.cpu.reg.F, 0b00110000);
}

TEST(PrefixedInstructions, BIT_3_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, BIT_3_A);
  game.mem.SetInAddr(0x102, OPCODE_PREFIX);
  game.mem.SetInAddr(0x103, BIT_3_A);
  game.cpu.reg.A = 0b00000000;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.F, 0b10100000);

  game.cpu.reg.A = 0b00001000;
  game.cpu.reg.F = 0b00010000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x104);
  EXPECT_EQ(game.cpu.reg.F, 0b00110000);
}

TEST(PrefixedInstructions, RR_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, RR_A);
  game.cpu.reg.A = 0b00100010;
  game.cpu.reg.F = 0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.A, 0b00010001);
}

TEST(PrefixedInstructions, RR_A_instruction_flags) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, RR_A);
  game.mem.SetInAddr(0x102, OPCODE_PREFIX);
  game.mem.SetInAddr(0x103, RR_A);
  game.cpu.reg.A = 0b00100010;
  game.cpu.reg.F = 0;
  utils::set_carry_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.A, 0b10010001);
  EXPECT_EQ(game.cpu.reg.F, 0b00000000);

  game.cpu.reg.A = 0b00000001;
  game.cpu.reg.F = 0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x104);
  EXPECT_EQ(game.cpu.reg.A, 0);
  EXPECT_EQ(game.cpu.reg.F, 0b10010000);
}

TEST(PrefixedInstructions, RES_7_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, RES_7_aHL);
  game.mem.SetInAddr(0x150, 0b11111111);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b01111111);
}

TEST(PrefixedInstructions, RES_1_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, RES_1_aHL);
  game.mem.SetInAddr(0x150, 0b11111010);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b11111000);
}


TEST(PrefixedInstructions, SET_7_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SET_7_aHL);
  game.mem.SetInAddr(0x150, 0b01111111);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b11111111);
}

TEST(PrefixedInstructions, SET_4_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SET_4_aHL);
  game.mem.SetInAddr(0x150, 0b00100000);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b00110000);
}

TEST(PrefixedInstructions, SET_1_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SET_1_aHL);
  game.mem.SetInAddr(0x150, 0b11111000);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b11111010);
}

TEST(PrefixedInstructions, SET_0_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SET_0_aHL);
  game.mem.SetInAddr(0x150, 0b11111000);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0x150), 0b11111001);
}

TEST(PrefixedInstructions, SRL_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SRL_A);
  game.cpu.reg.A = 0b11000010;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.A, 0b01100001);
}

TEST(PrefixedInstructions, SRL_A_instruction_flags) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SRL_A);
  game.cpu.reg.A = 0b11000011;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.A, 0b01100001);
  EXPECT_EQ(game.cpu.reg.F, 0b00010000);

  game.cpu.reg.PC = 0x100;
  game.cpu.reg.A = 0b00000001;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(game.cpu.reg.F, 0b10010000);
}

TEST(PrefixedInstructions, SRL_B_instruction_flags) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SRL_B);
  game.cpu.reg.B = 0b11000011;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.B, 0b01100001);
  EXPECT_EQ(game.cpu.reg.F, 0b00010000);

  game.cpu.reg.PC = 0x100;
  game.cpu.reg.B = 0b00000001;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.reg.B, 0x0);
  EXPECT_EQ(game.cpu.reg.F, 0b10010000);
}

TEST(PrefixedInstructions, SWAP_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SWAP_A);
  game.cpu.reg.A = 0b11001011;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b10111100);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(PrefixedInstructions, SWAP_A_instruction_zero_flag) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, OPCODE_PREFIX);
  game.mem.SetInAddr(0x101, SWAP_A);
  game.cpu.reg.A = 0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}
