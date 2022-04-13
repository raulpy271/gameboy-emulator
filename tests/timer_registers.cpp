
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"
#include "../src/game/timer_registers.h"

TEST(Timer, DIV_register) {
  unsigned int div_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, 0, 0, 0, 0);

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
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, 0, 0, 0, 0);

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

TEST(Timer, TAC_register_stop_mode) {
  unsigned int div_clock_frequency = 5;
  unsigned int tac_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, tac_clock_frequency, 0, 0, 0);

  mem.SetInAddr(rTAC, 0); // stop rTIME register 

  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x00);
  timer.pulses(5);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x00);
}

TEST(Timer, TAC_register_start_mode) {
  unsigned int div_clock_frequency = 5;
  unsigned int tac_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, tac_clock_frequency, 0, 0, 0);

  mem.SetInAddr(rTAC, 0b00000100); // start rTIME register 

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x00);

  timer.pulses(4);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);
}

TEST(Timer, TAC_register_different_numbers_of_pulses) {
  unsigned int div_clock_frequency = 5;
  unsigned int tac_clock_frequency = 5;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, tac_clock_frequency, 0, 0, 0);

  mem.SetInAddr(rTAC, 0b00000100); // start rTIME register 

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x00);

  timer.pulses(6);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);

  timer.pulses(1);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x02);
}

TEST(Timer, TAC_register_changing_frequency) {
  unsigned int div_clock_frequency = 5;
  unsigned int tac_clock_frequency_00 = 5;
  unsigned int tac_clock_frequency_01 = 10;
  gameboy::Memory mem;
  gameboy::TimerRegisters timer(&mem, div_clock_frequency, tac_clock_frequency_00, tac_clock_frequency_01, 0, 0);

  mem.SetInAddr(rTAC, 0b00000100); // start rTIME register 

  timer.pulses(5);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);

  mem.SetInAddr(rTAC, 0b00000101); // set frequency to select 01

  timer.pulses(5);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x01);

  timer.pulses(5);
  EXPECT_EQ(mem.GetInAddr(rTIMA), 0x02);
}
