
#include <iostream>

#include "primitives.h"
#include "timer_registers.h"
#include "hardware_registers.h"

namespace gameboy {

TimerRegisters::TimerRegisters(Memory* mem, unsigned int div_clock_frequency) {
  this->mem = mem;
  div_frequency = div_clock_frequency;
  pulses_until_div_frequency = div_clock_frequency;
}

void TimerRegisters::pulses(unsigned int pulses) {
  if ((int)(pulses_until_div_frequency - pulses) <= 0) {
    pulses_until_div_frequency = div_frequency - (pulses - pulses_until_div_frequency);
    mem->IncrementDivRegister();
  } else {
    pulses_until_div_frequency -= pulses;
  }
}

}