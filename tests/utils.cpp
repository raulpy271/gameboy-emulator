
#include <utility>

#include <gtest/gtest.h>

#include "../src/game/primitives.h"
#include "../src/game/cpu/interrupts.h"
#include "../src/utils/functions.h"

TEST(Utils, create_two_bytes_from_address) {
  std::pair<Byte, Byte> two_bytes;

  two_bytes = utils::create_two_bytes_from_address(0);

  EXPECT_EQ(0, two_bytes.first);
  EXPECT_EQ(0, two_bytes.second);

  two_bytes = utils::create_two_bytes_from_address(0x0150);

  EXPECT_EQ(0x01, two_bytes.first);
  EXPECT_EQ(0x50, two_bytes.second);

  two_bytes = utils::create_two_bytes_from_address(0xffff);

  EXPECT_EQ(0xff, two_bytes.first);
  EXPECT_EQ(0xff, two_bytes.second);
}


TEST(Utils, GetInterruptHandlingAddress) {
  Address vblank_addr = 0x40;
  Address serial_addr = 0x58;
  Address joypad_addr = 0x60;

  EXPECT_EQ(vblank_addr, utils::GetInterruptHandlingAddress(gameboy::InterruptFlag::VBLANK));
  EXPECT_EQ(serial_addr, utils::GetInterruptHandlingAddress(gameboy::InterruptFlag::SERIAL));
  EXPECT_EQ(joypad_addr, utils::GetInterruptHandlingAddress(gameboy::InterruptFlag::HiToLo));
}