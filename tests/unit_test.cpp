
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/cpu/opcodes.h"
#include "../src/utils/register_F_manipulate.h"

TEST(Instructions, JP_a16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, JP_HL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_HL, true);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, LD_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_d8, true);
  game.mem.SetInAddr(0x101, to_load, true);
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_B_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_d8, true);
  game.mem.SetInAddr(0x101, to_load, true);
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_C_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_C_d8, true);
  game.mem.SetInAddr(0x101, to_load, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_D_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_D_d8, true);
  game.mem.SetInAddr(0x101, to_load, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_E_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_E_d8, true);
  game.mem.SetInAddr(0x101, to_load, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.E, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_a8_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_a8_A, true);
  game.mem.SetInAddr(0x101, 0xF0, true);
  game.cpu.reg.A = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0xFFF0), game.cpu.reg.A);
}

TEST(Instructions, LD_a16_A_instruction) {
  gameboy::Console game;
  Address address_to_store = 0x8050;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_a16_A, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x80, true);
  game.mem.SetInAddr(address_to_store, 0x0);
  game.cpu.reg.A = 0x50;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
  EXPECT_EQ(game.mem.GetInAddr(address_to_store), game.cpu.reg.A);
}

TEST(Instructions, LD_aC_A_instruction) {
  gameboy::Console game;
  Byte byte_to_store = 0x15;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aC_A, true);
  game.cpu.reg.A = byte_to_store;
  game.cpu.reg.C = 0xf0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.mem.GetInAddr(0xFF00 + game.cpu.reg.C), byte_to_store);
}

TEST(Instructions, LD_A_a16_instruction) {
  gameboy::Console game;
  Address address_to_store = 0x150;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.mem.SetInAddr(address_to_store, 0x50, true);
  game.cpu.reg.A = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_A_a8_instruction) {
  gameboy::Console game;
  Address address_to_store = 0x150;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_a8, true);
  game.mem.SetInAddr(0x101, 0xfe, true);
  game.mem.SetInAddr(0xfffe, 0x50);
  game.cpu.reg.A = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, CP_d8_instruction_true_case) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, CP_d8, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.cpu.reg.A = 0x50;
  game.cpu.reg.F = 0b00000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);

  game.initialize_registers();
  game.cpu.reg.A = 0x50;
  game.cpu.reg.F = 0b01000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);

}

TEST(Instructions, CP_d8_instruction_false_case) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, CP_d8, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.cpu.reg.A = 0x49;
  game.cpu.reg.F = 0b11000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, CP_A_aHL_instruction_true_case) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, CP_A_aHL, true);
  game.mem.SetInAddr(0xFFFF, 0x50);
  game.cpu.reg.A = 0x50;
  game.cpu.reg.H = 0xFF;
  game.cpu.reg.L = 0xFF;
  game.cpu.reg.F = 0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, PUSH_BC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, PUSH_BC, true);
  game.cpu.reg.B = 0x01;
  game.cpu.reg.C = 0x02;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x02);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
  EXPECT_EQ(game.cpu.reg.SP, sp_old_position - 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, PUSH_AF_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, PUSH_AF, true);
  game.cpu.reg.A = 0x01;
  game.cpu.reg.F = 0x02;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x02);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
  EXPECT_EQ(game.cpu.reg.SP, sp_old_position - 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, PUSH_DE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, PUSH_DE, true);
  game.cpu.reg.D = 0x01;
  game.cpu.reg.E = 0x02;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x02);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
  EXPECT_EQ(game.cpu.reg.SP, sp_old_position - 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, PUSH_HL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, PUSH_HL, true);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x02;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x02);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
  EXPECT_EQ(game.cpu.reg.SP, sp_old_position - 2);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, POP_HL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, POP_HL, true);
  game.mem.SetInAddr(0x150, 0x20, true);
  game.mem.SetInAddr(0x151, 0xaa, true);
  game.cpu.reg.SP = 0x0150;
  game.cpu.reg.H = 0x00;
  game.cpu.reg.L = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0xaa);
  EXPECT_EQ(game.cpu.reg.L, 0x20);
  EXPECT_EQ(game.cpu.reg.SP, 0x152);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, POP_DE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, POP_DE, true);
  game.mem.SetInAddr(0x150, 0x20, true);
  game.mem.SetInAddr(0x151, 0xaa, true);
  game.cpu.reg.SP = 0x0150;
  game.cpu.reg.D = 0x00;
  game.cpu.reg.E = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 0xaa);
  EXPECT_EQ(game.cpu.reg.E, 0x20);
  EXPECT_EQ(game.cpu.reg.SP, 0x152);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, POP_BC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, POP_BC, true);
  game.mem.SetInAddr(0x150, 0x20, true);
  game.mem.SetInAddr(0x151, 0xaa, true);
  game.cpu.reg.SP = 0x0150;
  game.cpu.reg.B = 0x00;
  game.cpu.reg.C = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0xaa);
  EXPECT_EQ(game.cpu.reg.C, 0x20);
  EXPECT_EQ(game.cpu.reg.SP, 0x152);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, POP_AF_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, POP_AF, true);
  game.mem.SetInAddr(0x150, 0x20, true);
  game.mem.SetInAddr(0x151, 0xaa, true);
  game.cpu.reg.SP = 0x0150;
  game.cpu.reg.A = 0x00;
  game.cpu.reg.F = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0xaa);
  EXPECT_EQ(game.cpu.reg.F, 0x20);
  EXPECT_EQ(game.cpu.reg.SP, 0x152);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, JP_C_a16_case_C_flag_reset) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, JP_C_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.cpu.reg.F = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_C_a16_case_C_flag_set) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, JP_C_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.cpu.reg.F = 0x0;
  utils::set_carry_flag(&game.cpu.reg.F, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
}

TEST(Instructions, LD_DE_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_DE_d16, true);
  game.mem.SetInAddr(0x101, 147, true);
  game.mem.SetInAddr(0x102, 1, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 1);
  EXPECT_EQ(game.cpu.reg.E, 147);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_HL_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_HL_d16, true);
  game.mem.SetInAddr(0x101, 0x0a, true);
  game.mem.SetInAddr(0x102, 0xbb, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0xbb);
  EXPECT_EQ(game.cpu.reg.L, 0x0a);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_BC_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_BC_d16, true);
  game.mem.SetInAddr(0x101, 0x0b, true);
  game.mem.SetInAddr(0x102, 0xbb, true);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0xbb);
  EXPECT_EQ(game.cpu.reg.C, 0x0b);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_SP_d16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_SP_d16, true);
  game.mem.SetInAddr(0x101, 0x0a, true);
  game.mem.SetInAddr(0x102, 0xbb, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.SP, 0xbb0a);
  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, LD_A_aBC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  game.mem.SetInAddr(0x100, LD_A_aBC, true);
  game.mem.SetInAddr(0x150, value_to_load_in_A, true);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.B = 0x01;
  game.cpu.reg.C = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_aDE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  game.mem.SetInAddr(0x100, LD_A_aDE, true);
  game.mem.SetInAddr(0x150, value_to_load_in_A, true);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.D = 0x01;
  game.cpu.reg.E = 0x50;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_A_aHL, true);
  game.mem.SetInAddr(0x150, value_to_load_in_A, true);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_aHLI_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_A_aHLI, true);
  game.mem.SetInAddr(0x150, value_to_load_in_A, true);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.L, 0x51);
}

TEST(Instructions, LD_A_aHLI_instruction_overflow) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  game.mem.SetInAddr(0x100, LD_A_aHLI, true);
  game.mem.SetInAddr(0xffff, value_to_load_in_A);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.H = 0xff;
  game.cpu.reg.L = 0xff;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.cpu.reg.H, 0x00);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
}

TEST(Instructions, LD_A_aHLD_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  game.mem.SetInAddr(0x100, LD_A_aHLD, true);
  game.mem.SetInAddr(0x150, value_to_load_in_A, true);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.L, 0x4F);
}

TEST(Instructions, LD_aHL_d8_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_d8, true);
  game.mem.SetInAddr(0x101, 0x10, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_aHL_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_A, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHL_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_C, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.C = 0x15;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x15);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHL_D_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_D, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.D = 0x10;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHL_E_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_E, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.E = 0x10;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aDE_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aDE_A, true);
  game.mem.SetInAddr(0x8150, 0x0, true);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.D = 0x81;
  game.cpu.reg.E = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x8150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLI_A_instruction_increment_L) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLI_A, true);
  game.mem.SetInAddr(0x9150, 0x0, true);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x91;
  game.cpu.reg.L = 0x50;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x9150), game.cpu.reg.A);
  EXPECT_EQ(game.cpu.reg.L, 0x51);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLI_A_instruction_increment_both_registers) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLI_A, true);
  game.mem.SetInAddr(0x81ff, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0xff;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x81ff), game.cpu.reg.A);
  EXPECT_EQ(game.cpu.reg.H, 0x82);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLD_A_instruction_decrement_L) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLD_A, true);
  game.mem.SetInAddr(0x81ff, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x81;
  game.cpu.reg.L = 0xff;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x81ff), 0x10);
  EXPECT_EQ(game.cpu.reg.H, 0x81);
  EXPECT_EQ(game.cpu.reg.L, 0xfe);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLD_A_instruction_decrement_H) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLD_A, true);
  game.mem.SetInAddr(0xa000, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0xa0;
  game.cpu.reg.L = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0xa000), 0x10);
  EXPECT_EQ(game.cpu.reg.H, 0x9f);
  EXPECT_EQ(game.cpu.reg.L, 0xff);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLD_A_instruction_underflow) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLD_A);
  game.mem.SetInAddr(0x0, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x00;
  game.cpu.reg.L = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x0), 0x10);
  EXPECT_EQ(game.cpu.reg.H, 0xff);
  EXPECT_EQ(game.cpu.reg.L, 0xff);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_B, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.B = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_D_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_D, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.D = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_E_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_E, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.E = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_L_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_L, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.L = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_D_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_D_A, true);
  game.cpu.reg.D = 0x00;
  game.cpu.reg.A = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.D, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_E_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_E_A, true);
  game.cpu.reg.E = 0x00;
  game.cpu.reg.A = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.E, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_E_L_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_E_L, true);
  game.cpu.reg.E = 0x00;
  game.cpu.reg.L = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(game.cpu.reg.E, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_H_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_H_A, true);
  game.cpu.reg.A = 0x01;
  game.cpu.reg.H = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_H_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_H_B, true);
  game.cpu.reg.B = 0x01;
  game.cpu.reg.H = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x01);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_H_D_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_H_D, true);
  game.cpu.reg.H = 0x00;
  game.cpu.reg.D = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 0x01);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_H_d8_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_H_d8, true);
  game.mem.SetInAddr(0x101, 0x01, true);
  game.cpu.reg.H = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_L_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_L_A, true);
  game.cpu.reg.A = 0x01;
  game.cpu.reg.L = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_L_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_L_C, true);
  game.cpu.reg.C = 0x01;
  game.cpu.reg.L = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x01);
  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_L_E_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_L_E, true);
  game.cpu.reg.E = 0x01;
  game.cpu.reg.L = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(game.cpu.reg.E, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_C, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.C = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_C_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_C_A, true);
  game.cpu.reg.A = 0x20;
  game.cpu.reg.C = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_H_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_H, true);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.H = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.H, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_A, true);
  game.cpu.reg.A = 0x20;
  game.cpu.reg.B = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_B, true);
  game.cpu.reg.B = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_C, true);
  game.cpu.reg.C = 0x20;
  game.cpu.reg.B = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_D_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_D, true);
  game.cpu.reg.B = 0x00;
  game.cpu.reg.D = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_E_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_E, true);
  game.cpu.reg.B = 0x00;
  game.cpu.reg.E = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_H_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_H, true);
  game.cpu.reg.B = 0x00;
  game.cpu.reg.H = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_L_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_L, true);
  game.cpu.reg.B = 0x00;
  game.cpu.reg.L = 0x20;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_B_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_aHL, true);
  game.mem.SetInAddr(0x150, 0x50, true);
  game.cpu.reg.B = 0x00;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_C_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_C_aHL, true);
  game.mem.SetInAddr(0x150, 0x50, true);
  game.cpu.reg.C = 0x00;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_D_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_D_aHL, true);
  game.mem.SetInAddr(0x150, 0x50, true);
  game.cpu.reg.D = 0x00;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_E_aHL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_E_aHL, true);
  game.mem.SetInAddr(0x150, 0x50, true);
  game.cpu.reg.E = 0x00;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.E, 0x50);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, JR_NZ_s8_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, JR_NZ_s8_instruction_forward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x8);
}

TEST(Instructions, JR_NZ_s8_instruction_backward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8, true);
  game.mem.SetInAddr(0x101, 0xF7, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 - 0x9);
}

TEST(Instructions, JR_Z_s8_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_Z_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, JR_Z_s8_instruction_forward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_Z_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x8);
}

TEST(Instructions, JR_Z_s8_instruction_backward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_Z_s8, true);
  game.mem.SetInAddr(0x101, 0xF7, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 - 0x9);
}

TEST(Instructions, JR_C_s8_instruction_carry_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_C_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, JR_C_s8_instruction_forward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_C_s8, true);
  game.mem.SetInAddr(0x101, 0x8, true);
  game.cpu.reg.F = 0x0;
  utils::set_carry_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x8);
}

TEST(Instructions, JP_NZ_a16_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NZ_a16, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_NZ_a16_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NZ_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0150);
}

TEST(Instructions, JP_Z_a16_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_Z_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x10, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x1050);
}

TEST(Instructions, JP_Z_a16_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_Z_a16, true);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_NC_a16_instruction_carry_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NC_a16, true);
  game.cpu.reg.F = 0x0;
  utils::set_carry_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_NC_a16_instruction_carry_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NC_a16, true);
  game.mem.SetInAddr(0x101, 0x60, true);
  game.mem.SetInAddr(0x102, 0x02, true);
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0260);
}

TEST(Instructions, CALL_a16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.PC = 0x150;

  game.mem.SetInAddr(0x150, CALL_a16, true);
  game.mem.SetInAddr(0x151, 0x90, true);
  game.mem.SetInAddr(0x152, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x290);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x53);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
}

TEST(Instructions, CALL_Z_a16_instruction_z_is_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, CALL_Z_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CALL_Z_a16_instruction_z_is_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_zero_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, CALL_Z_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x290);
}

TEST(Instructions, CALL_NZ_a16_instruction_z_is_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_zero_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, CALL_NZ_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CALL_NZ_a16_instruction_z_is_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, CALL_NZ_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0290);
}

TEST(Instructions, CALL_C_a16_instruction_carry_is_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, CALL_C_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CALL_C_a16_instruction_carry_is_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_carry_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, CALL_C_a16, true);
  game.mem.SetInAddr(0x101, 0x90, true);
  game.mem.SetInAddr(0x102, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0290);
}

TEST(Instructions, RET_instruction) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, RET, true);
  game.mem.SetInAddr(game.cpu.reg.SP - 1, 0x01);
  game.mem.SetInAddr(game.cpu.reg.SP - 2, 0x50);
  Address old_sp = game.cpu.reg.SP;
  game.cpu.reg.SP -= 2;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);
  EXPECT_EQ(game.cpu.reg.SP, old_sp);
}

TEST(Instructions, RET_Z_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, RET_Z, true);
  game.cpu.reg.F = 0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, RET_Z_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_zero_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, RET_Z, true);
  game.mem.SetInAddr(game.cpu.reg.SP - 1, 0x01);
  game.mem.SetInAddr(game.cpu.reg.SP - 2, 0x50);
  game.cpu.reg.SP -= 2;


  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0150);
}

TEST(Instructions, RET_NC_instruction_carry_is_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_carry_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, RET_NC, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, RET_NC_instruction_carry_is_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, CALL_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.mem.SetInAddr(0x150, RET_NC, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);

  utils::set_carry_flag(&game.cpu.reg.F, false);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, RET_NZ_instruction_zero_is_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_zero_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, RET_NZ, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, RET_NZ_instruction_zero_is_not_set) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  game.mem.SetInAddr(0x100, CALL_a16, true);
  game.mem.SetInAddr(0x101, 0x50, true);
  game.mem.SetInAddr(0x102, 0x01, true);
  game.mem.SetInAddr(0x150, RET_NZ, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x150);

  utils::set_zero_flag(&game.cpu.reg.F, false);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CALL_and_RET_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.PC = 0x150;

  game.mem.SetInAddr(0x150, CALL_a16, true);
  game.mem.SetInAddr(0x151, 0x90, true);
  game.mem.SetInAddr(0x152, 0x02, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x290);

  game.mem.SetInAddr(0x290, RET, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x153);
}

TEST(Instructions, JR_s8_instruction) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, JR_s8, true);
  game.mem.SetInAddr(0x101, 0x4e, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x4e);
}

TEST(Instructions, JR_s8_instruction_backward) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, JR_s8, true);
  game.mem.SetInAddr(0x101, 0xfc, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 - 0x4);
}

TEST(Instructions, CCF_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0b00000000;
  game.mem.SetInAddr(0x100, CCF, true);
  game.mem.SetInAddr(0x101, CCF, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.F, 0b00010000);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.reg.F = 0b11110000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.F, 0b10000000);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, RLCA_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, RLCA, true);
  game.cpu.reg.A = 0b01000011;
  game.cpu.reg.F = 0x0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.cpu.reg.A, 0b10000110);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::carry_flag(&game.cpu.reg.F), false);
}

TEST(Instructions, CPL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.A = 0b01000101;
  game.mem.SetInAddr(0x100, CPL, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0b10111010);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::half_carry_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, RST_0x28_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x1150, RST_0x28, true);
  game.cpu.reg.PC = 0x1150;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x28);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x51);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x11);
}

TEST(Instructions, RST_0x28_and_RET_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x28, RET, true);
  game.mem.SetInAddr(0x100, RST_0x28, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x28);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}
