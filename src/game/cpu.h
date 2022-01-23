
#ifndef GAME_CPU_H_
#define GAME_CPU_H_

#include "primitives.h"

struct Registers {
  Byte A, F;
  Byte B, C;
  Byte D, E;
  Byte H, L;
  Address SP;
  Address PC;
};

#endif  // GAME_CPU_H_
