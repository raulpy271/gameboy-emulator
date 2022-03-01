
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/cpu/opcodes.h"
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

TEST(Instructions, LD_B_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_B_d8);
  game.mem.SetInAddr(0x101, to_load);
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_C_d8_instruction) {
  gameboy::Console game;
  int to_load = 0x50;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_C_d8);
  game.mem.SetInAddr(0x101, to_load);
  game.cpu.reg.A = 0x00;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, to_load);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, LD_a8_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_a8_A);
  game.mem.SetInAddr(0x101, 0xF0);
  game.cpu.reg.A = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.mem.GetInAddr(0xFFF0), game.cpu.reg.A);
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

TEST(Instructions, LD_aC_A_instruction) {
  gameboy::Console game;
  Byte byte_to_store = 0x15;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aC_A);
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
  game.cpu.reg.A = 0x50;
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
  game.cpu.reg.F = 0b11000000;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
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

TEST(Instructions, LD_A_aDE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  Byte value_to_load_in_A = 0x0a;
  Address sp_old_position = game.cpu.reg.SP; 
  game.mem.SetInAddr(0x100, LD_A_aDE);
  game.mem.SetInAddr(0x150, value_to_load_in_A);
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
  game.mem.SetInAddr(0x100, LD_A_aHL);
  game.mem.SetInAddr(0x150, value_to_load_in_A);
  game.cpu.reg.A = 0x0;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, value_to_load_in_A);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHL_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHL_A);
  game.mem.SetInAddr(0x150, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x0150), 0x10);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLI_A_instruction_increment_L) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLI_A);
  game.mem.SetInAddr(0x150, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0x50;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x0150), game.cpu.reg.A);
  EXPECT_EQ(game.cpu.reg.L, 0x51);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_aHLI_A_instruction_increment_both_registers) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_aHLI_A);
  game.mem.SetInAddr(0x01ff, 0x0);
  game.cpu.reg.A = 0x10;
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0xff;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.mem.GetInAddr(0x01ff), game.cpu.reg.A);
  EXPECT_EQ(game.cpu.reg.H, 0x02);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, INC_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, INC_A);
  game.mem.SetInAddr(0x101, INC_A);
  game.cpu.reg.A = 0xfe;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0xff);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, INC_DE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, INC_DE);
  game.mem.SetInAddr(0x101, INC_DE);
  game.cpu.reg.D = 0x01;
  game.cpu.reg.E = 0xff;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 0x02);
  EXPECT_EQ(game.cpu.reg.E, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.D, 0x02);
  EXPECT_EQ(game.cpu.reg.E, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, INC_HL_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, INC_HL);
  game.mem.SetInAddr(0x101, INC_HL);
  game.cpu.reg.H = 0x01;
  game.cpu.reg.L = 0xff;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x02);
  EXPECT_EQ(game.cpu.reg.L, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.H, 0x02);
  EXPECT_EQ(game.cpu.reg.L, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, DEC_BC_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, DEC_BC);
  game.mem.SetInAddr(0x101, DEC_BC);
  game.cpu.reg.B = 0x01;
  game.cpu.reg.C = 0x01;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x01);
  EXPECT_EQ(game.cpu.reg.C, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.B, 0x00);
  EXPECT_EQ(game.cpu.reg.C, 0xff);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, DEC_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, DEC_C);
  game.mem.SetInAddr(0x101, DEC_C);
  game.cpu.reg.C = 0x02;
  game.cpu.reg.F = 0x0;
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), false);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x00);
  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(utils::zero_flag(&game.cpu.reg.F), true);
  EXPECT_EQ(utils::subtract_flag(&game.cpu.reg.F), true);
}

TEST(Instructions, LD_A_B_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_B);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.B = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_A_C_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_A_C);
  game.cpu.reg.A = 0x00;
  game.cpu.reg.C = 0x01;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x01);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, LD_C_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, LD_C_A);
  game.cpu.reg.A = 0x20;
  game.cpu.reg.C = 0x00;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.C, 0x20);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, XOR_A_A_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, XOR_A_A);
  game.cpu.reg.A = 0b00000100;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.A, 0x0);
  EXPECT_EQ(game.cpu.reg.F, 0b10000000);
  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, OR_A_C_instruction) {
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

TEST(Instructions, OR_A_C_instruction_affect_zero_flag) {
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

TEST(Instructions, OR_A_B_instruction) {
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

TEST(Instructions, OR_A_B_instruction_affect_zero_flag) {
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

TEST(Instructions, JR_NZ_s8_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8);
  game.mem.SetInAddr(0x101, 0x8);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
}

TEST(Instructions, JR_NZ_s8_instruction_forward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8);
  game.mem.SetInAddr(0x101, 0x8);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x8);
}

TEST(Instructions, JR_NZ_s8_instruction_backward) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JR_NZ_s8);
  game.mem.SetInAddr(0x101, 0xF7);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 - 0x9);
}

TEST(Instructions, JP_NZ_a16_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NZ_a16);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, JP_NZ_a16_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_NZ_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0150);
}

TEST(Instructions, JP_Z_a16_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_Z_a16);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x10);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, true);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x1050);
}

TEST(Instructions, JP_Z_a16_instruction_nonzero) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, JP_Z_a16);
  game.cpu.reg.F = 0x0;
  utils::set_zero_flag(&game.cpu.reg.F, false);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x103);
}

TEST(Instructions, CALL_a16_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.PC = 0x150;

  game.mem.SetInAddr(0x150, CALL_a16);
  game.mem.SetInAddr(0x151, 0x90);
  game.mem.SetInAddr(0x152, 0x02);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x290);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP), 0x53);
  EXPECT_EQ(game.mem.GetInAddr(game.cpu.reg.SP + 1), 0x01);
}

TEST(Instructions, RET_instruction) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, RET);
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

  game.mem.SetInAddr(0x100, RET_Z);
  game.cpu.reg.F = 0;

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
}

TEST(Instructions, RET_Z_instruction_zero) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.F = 0;
  utils::set_zero_flag(&game.cpu.reg.F, true);
  game.mem.SetInAddr(0x100, RET_Z);
  game.mem.SetInAddr(game.cpu.reg.SP - 1, 0x01);
  game.mem.SetInAddr(game.cpu.reg.SP - 2, 0x50);
  game.cpu.reg.SP -= 2;


  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x0150);
}

TEST(Instructions, CALL_and_RET_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.cpu.reg.PC = 0x150;

  game.mem.SetInAddr(0x150, CALL_a16);
  game.mem.SetInAddr(0x151, 0x90);
  game.mem.SetInAddr(0x152, 0x02);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x290);

  game.mem.SetInAddr(0x290, RET);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x153);
}

TEST(Instructions, JR_s8_instruction) {
  gameboy::Console game;
  game.initialize_registers();

  game.mem.SetInAddr(0x100, JR_s8);
  game.mem.SetInAddr(0x101, 0x4e);

  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102 + 0x4e);
}

