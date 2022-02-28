
#ifndef GAME_INTERRUPTS_H_
#define GAME_INTERRUPTS_H_

namespace gameboy {

enum class InterruptVector {
  VBLANK = 0x40,
  LCDC   = 0x48,
  SERIAL = 0x50,
  TIMER  = 0x58,
  HiToLo = 0x60
};

enum class InterruptFlag {
  VBLANK      = 0,
  LCDC        = 1,
  SERIAL      = 2,
  TIMER       = 3,
  HiToLo      = 4,
  NoInterrupt = 5
};

}

#endif  // GAME_INTERRUPTS_H_