
#include <bitset>

#include "keypad.h"
#include "hardware_registers.h"

namespace gameboy {

Keypad::Keypad() {
  selected_action_bottons = false;
  selected_direction_bottons = false;
  for (int i = 0; i < BOTTONS_LEN; i++) {
    pressed_botton[i] = false;
  }
}

void Keypad::PressBotton(Botton botton) {
  pressed_botton[(int) botton] = true;
}

void Keypad::ReleaseBotton(Botton botton) {
  pressed_botton[(int) botton] = false;
}

Byte Keypad::WriteOnP1Register(Byte value) {
  std::bitset<8> result(value);
  bool select_action_bottons    = (~value) & 0b00100000;
  bool select_direction_bottons = (~value) & 0b00010000;
  selected_direction_bottons = select_direction_bottons;
  selected_action_bottons = select_action_bottons;
  if (select_action_bottons) {
    return 0b00011111;
  }
  if (select_direction_bottons) {
    return 0b00101111;
  }
  return 0b00111111;
}

Byte Keypad::ReadOnP1Register(Byte value) {
  std::bitset<8> result(value);
  if (selected_direction_bottons) {
    result[0] = !(pressed_botton[(int) Botton::Right]);
    result[1] = !(pressed_botton[(int) Botton::Left]);
    result[2] = !(pressed_botton[(int) Botton::Up]);
    result[3] = !(pressed_botton[(int) Botton::Down]);
    return result.to_ulong();
  }
  return 0b00111111;
}

}