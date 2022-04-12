
#ifndef GAME_TIMER_REGISTERS_H_
#define GAME_TIMER_REGISTERS_H_

#include "memory.h"

namespace gameboy {

class TimerRegisters {

public:

  TimerRegisters(Memory* mem, unsigned int div_clock_frequency);

  void pulses(unsigned int pulses);

private:

  Memory* mem;

  unsigned int div_frequency;

  unsigned int pulses_until_div_frequency;

};

}

#endif  // GAME_TIMER_REGISTERS_H_