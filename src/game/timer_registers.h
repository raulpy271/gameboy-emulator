
#ifndef GAME_TIMER_REGISTERS_H_
#define GAME_TIMER_REGISTERS_H_

#include "memory.h"

namespace gameboy {

class TimerRegisters {

public:

  TimerRegisters(
    Memory* mem, 
    unsigned int div_clock_frequency,
    unsigned int tac_clock_select_00,
    unsigned int tac_clock_select_01,
    unsigned int tac_clock_select_10,
    unsigned int tac_clock_select_11
  );

  void pulses(unsigned int pulses);

private:

  Memory* mem;

  unsigned int div_frequency;
  unsigned int current_tima_frequency;
  unsigned int tac_clock_select_00;
  unsigned int tac_clock_select_01;
  unsigned int tac_clock_select_10;
  unsigned int tac_clock_select_11;

  unsigned int pulses_until_div_frequency;
  unsigned int pulses_until_tima_frequency;

  bool TIMARegisterStart();

  unsigned int TIMARegisterFrequency();

};

}

#endif  // GAME_TIMER_REGISTERS_H_