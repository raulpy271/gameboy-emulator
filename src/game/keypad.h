
#ifndef GAME_KEYPAD_H_
#define GAME_KEYPAD_H_

#include "primitives.h"

#define BOTTONS_LEN 8

namespace gameboy {

enum class Botton {
  A      = 0,
  B      = 1,
  Start  = 2,
  Select = 3,
  Up     = 4,
  Down   = 5,
  Left   = 6,
  Right  = 7,
};

class Keypad {
 public:
  Keypad();

  void PressBotton(Botton botton);

  void ReleaseBotton(Botton botton);

  Byte WriteOnP1Register(Byte value);

  Byte ReadOnP1Register(Byte value);

 private:
  bool pressed_botton[BOTTONS_LEN]; 
  bool selected_action_bottons;
  bool selected_direction_bottons;

};


}

#endif  // GAME_KEYPAD_H_
