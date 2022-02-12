
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/opcodes.h"
#include "../src/utils/register_F_manipulate.h"

TEST(Instructions, JP_a16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, LD_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_d8);
  game.mem.SetInAddr(0x101, to_load);
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_a16_A_instruction) {
  gameboy::Console game;
  Address address_to_store = 0x150;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_a16_A);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.mem.SetInAddr(address_to_store, 0x0);
  game.cpu.reg.A = 0x50;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
  EXPECT_EQ(game.mem.GetInAddr(address_to_store), game.cpu.reg.A);
}

TEST(Instructions, LD_A_a16_instruction) {
  gameboy::Console game;
  Address address_to_store = 0x150;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.mem.SetInAddr(address_to_store, 0x50);
  game.cpu.reg.A = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CP_d8_instruction_true_case) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, CP_d8);
  game.mem.SetInAddr(0x101, 0x50);
  game.cpu.reg.A = 0x50;
  game.cpu.reg.F = 0b00000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.F, 0b10000000);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);

  game.initialize_registers();
  game.cpu.reg.F = 0b01000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);

}

TEST(Instructions, CP_d8_instruction_false_case) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, CP_d8);
  game.mem.SetInAddr(0x101, 0x50);
  game.cpu.reg.A = 0x49;
  game.cpu.reg.F = 0b01000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.F, 0b01000000);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, PUSH_BC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, PUSH_BC);
  game.cpu.reg.B = 0x01;
  game.cpu.reg.C = 0x02;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x02);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
  EXPECT_EQ(game.cpu.reg.SP, sp_old_position - 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, JP_C_a16_case_C_flag_reset) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, JP_C_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.reg.F = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_C_a16_case_C_flag_set) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, JP_C_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.reg.F = 0x0;
  utils::set_carry_flag(&game.cpu.reg.F, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, LD_DE_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_DE_d16);
  game.mem.SetInAddr(0x101, 147);
  game.mem.SetInAddr(0x102, 1);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 1);
  EXPECT_EQ(game.cpu.reg.E, 147);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_HL_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_HL_d16);
  game.mem.SetInAddr(0x101, 0x0a);
  game.mem.SetInAddr(0x102, 0xbb);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0xbb);
  EXPECT_EQ(game.cpu.reg.L, 0x0a);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_BC_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_BC_d16);
  game.mem.SetInAddr(0x101, 0x0b);
  game.mem.SetInAddr(0x102, 0xbb);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0xbb);
  EXPECT_EQ(game.cpu.reg.C, 0x0b);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}
