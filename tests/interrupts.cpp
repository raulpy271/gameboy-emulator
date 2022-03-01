
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/cpu/opcodes.h"
#include "../src/game/cpu/interrupts.h"
#include "../src/game/hardware_registers.h"

TEST(Interrupts, IE_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, IE);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x101);
  EXPECT_EQ(game.cpu.GetIME(), true);
}

TEST(Interrupts, DI_instruction) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(0x100, IE);
  game.mem.SetInAddr(0x101, DI);

  game.cpu.execute_intruction(&game.mem);
  game.cpu.execute_intruction(&game.mem);

  EXPECT_EQ(game.cpu.reg.PC, 0x102);
  EXPECT_EQ(game.cpu.GetIME(), false);
}

TEST(Interrupts, request_interrupts) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(rIF, 0x0);

  game.cpu.RequestInterrupt(&game.mem, gameboy::InterruptFlag::VBLANK);
  game.cpu.RequestInterrupt(&game.mem, gameboy::InterruptFlag::HiToLo);

  EXPECT_EQ(game.mem.GetInAddr(rIF), 0b00010001);
}

TEST(Interrupts, get_next_interrupt) {
  gameboy::InterruptFlag interrupt;
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(rIF, 0b00000010);
  game.mem.SetInAddr(rIE, 0b00000010);
  game.mem.SetInAddr(0x100, IE);
  game.run_a_instruction_cycle();

  interrupt = game.cpu.GetNextInterrupt(&game.mem);

  EXPECT_EQ(interrupt, gameboy::InterruptFlag::LCDC);

  game.mem.SetInAddr(rIF, 0b00000001);
  game.mem.SetInAddr(rIE, 0b00000001);

  interrupt = game.cpu.GetNextInterrupt(&game.mem);

  EXPECT_EQ(interrupt, gameboy::InterruptFlag::VBLANK);
}

TEST(Interrupts, get_next_interrupt_without_interrupt_enable) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(rIF, 0b00000001);
  game.mem.SetInAddr(rIE, 0b00000010);
  game.mem.SetInAddr(0x100, IE);

  game.run_a_instruction_cycle();

  gameboy::InterruptFlag interrupt = game.cpu.GetNextInterrupt(&game.mem);

  EXPECT_EQ(interrupt, gameboy::InterruptFlag::NoInterrupt);
}
