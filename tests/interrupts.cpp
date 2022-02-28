
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

TEST(Interrupts, request_interrupts) {
  gameboy::Console game;
  game.initialize_registers();
  game.mem.SetInAddr(rIF, 0x0);

  game.cpu.RequestInterrupt(&game.mem, gameboy::InterruptFlag::VBLANK);
  game.cpu.RequestInterrupt(&game.mem, gameboy::InterruptFlag::HiToLo);

  EXPECT_EQ(game.mem.GetInAddr(rIF), 0b00010001);
}
