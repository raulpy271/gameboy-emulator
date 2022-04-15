
#include <gtest/gtest.h>

#include "../src/game/memory.h"
#include "../src/game/keypad.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"

TEST(Keypad, press_up) {
  gameboy::Memory mem;
  Byte select_direction_bottons = 0b00101111;

  mem.SetInAddr(rP1, select_direction_bottons);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, 0b1011);
}

TEST(Keypad, release_up) {
  gameboy::Memory mem;
  Byte select_direction_bottons = 0b00101111;

  mem.SetInAddr(rP1, select_direction_bottons);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, 0b1011);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::RELEASE);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, 0b1111);
}
