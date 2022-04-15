
#include <gtest/gtest.h>

#include "../src/game/game.h"
#include "../src/game/keypad.h"
#include "../src/game/primitives.h"
#include "../src/game/hardware_registers.h"

TEST(Keypad, press_up) {
  gameboy::Console game;
  Byte select_direction_bottons = 0b00101111;
  Byte up_clicked = 0b1011;

  game.mem.SetInAddr(rP1, select_direction_bottons);

  game.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, up_clicked);
}

TEST(Keypad, release_up) {
  gameboy::Console game;
  Byte select_direction_bottons = 0b00101111;
  Byte up_clicked = 0b1011;
  Byte no_click = 0b1111;

  game.mem.SetInAddr(rP1, select_direction_bottons);

  game.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, up_clicked);

  game.HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::RELEASE);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, no_click);
}

TEST(Keypad, press_and_release_A) {
  gameboy::Console game;
  Byte select_action_bottons = 0b00011111;
  Byte A_clicked = 0b1110;
  Byte no_click = 0b1111;

  game.mem.SetInAddr(rP1, select_action_bottons);

  game.HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::PRESS);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, A_clicked);

  game.HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::RELEASE);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, no_click);
}

TEST(Keypad, press_down_and_B) {
  gameboy::Console game;
  Byte select_direction_bottons = 0b00100000;
  Byte select_action_bottons = 0b00010000;
  Byte down_clicked = 0b0111;
  Byte B_clicked = 0b1101;

  game.HandleBottonEvent(gameboy::Botton::Down, gameboy::BottonEventType::PRESS);
  game.HandleBottonEvent(gameboy::Botton::B, gameboy::BottonEventType::PRESS);

  game.mem.SetInAddr(rP1, select_direction_bottons);
  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, down_clicked);

  game.mem.SetInAddr(rP1, select_action_bottons);
  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, B_clicked);
}

TEST(Keypad, press_start_and_generate_interruption) {
  gameboy::Console game;
  Byte select_action_bottons = 0b00010000;
  Byte start_clicked = 0b0111;

  game.mem.SetInAddr(rIF, 0);
  game.HandleBottonEvent(gameboy::Botton::Start, gameboy::BottonEventType::PRESS);
  game.mem.SetInAddr(rP1, select_action_bottons);

  EXPECT_EQ(game.mem.GetInAddr(rP1) & 0b1111, start_clicked);
  EXPECT_EQ(game.mem.GetInAddr(rIF), 0b00010000);
}
