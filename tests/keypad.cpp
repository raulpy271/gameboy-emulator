
#include <gtest/gtest.h>

#include "../src/game/memory.h"
#include "../src/game/keypad.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"

TEST(Keypad, press_up) {
  gameboy::Memory mem;
  Byte select_direction_bottons = 0b00101111;
  Byte up_clicked = 0b1011;

  mem.SetInAddr(rP1, select_direction_bottons);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, up_clicked);
}

TEST(Keypad, release_up) {
  gameboy::Memory mem;
  Byte select_direction_bottons = 0b00101111;
  Byte up_clicked = 0b1011;
  Byte no_click = 0b1111;

  mem.SetInAddr(rP1, select_direction_bottons);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, up_clicked);

  mem.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::RELEASE);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, no_click);
}

TEST(Keypad, press_and_release_A) {
  gameboy::Memory mem;
  Byte select_action_bottons = 0b00011111;
  Byte A_clicked = 0b1110;
  Byte no_click = 0b1111;

  mem.SetInAddr(rP1, select_action_bottons);

  mem.HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, A_clicked);

  mem.HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::RELEASE);

  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, no_click);
}

TEST(Keypad, press_down_and_B) {
  gameboy::Memory mem;
  Byte select_direction_bottons = 0b00100000;
  Byte select_action_bottons = 0b00010000;
  Byte down_clicked = 0b0111;
  Byte B_clicked = 0b1101;

  mem.HandleBottonEvent(gameboy::Botton::Down, gameboy::BottonEventType::PRESS);
  mem.HandleBottonEvent(gameboy::Botton::B, gameboy::BottonEventType::PRESS);

  mem.SetInAddr(rP1, select_direction_bottons);
  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, down_clicked);

  mem.SetInAddr(rP1, select_action_bottons);
  EXPECT_EQ(mem.GetInAddr(rP1) & 0b1111, B_clicked);
}
