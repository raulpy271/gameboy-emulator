
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"
#include "../src/game/timer_registers.h"

TEST(Timer, DIV_register) {
  unsigned int div_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency);

  timer.pulses(div_clock_frequency - 1);

  EXPECT_EQ(mem.GetInAddr(rDIV), 0);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 1);

  timer.pulses(div_clock_frequency + 1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 2);

  timer.pulses(div_clock_frequency - 1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 3);
}

TEST(Timer, DIV_register_overflow) {
  unsigned int div_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency);

  for (int i = 0; i < 0xfe; i++) {
    mem.IncrementDivRegister();
  } 

  timer.pulses(div_clock_frequency - 1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 0xfe);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 0xff);

  timer.pulses(div_clock_frequency - 1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 0xff);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rDIV), 0x00);
}
