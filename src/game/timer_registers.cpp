
#include <iostream>
#include <bitset>

#include "primitives.h"
#include "timer_registers.h"
#include "hardware_registers.h"
#include "cpu/interrupts.h"

namespace gameboy {

TimerRegisters::TimerRegisters(
    Memory* mem, 
    unsigned int div_clock_frequency,
    unsigned int tac_clock_select_00,
    unsigned int tac_clock_select_01,
    unsigned int tac_clock_select_10,
    unsigned int tac_clock_select_11
    ) {
  this->mem = mem;
  this->tac_clock_select_00 = tac_clock_select_00;
  this->tac_clock_select_01 = tac_clock_select_01;
  this->tac_clock_select_10 = tac_clock_select_10;
  this->tac_clock_select_11 = tac_clock_select_11;
  div_frequency = div_clock_frequency;
  current_tima_frequency = TIMARegisterFrequency();
  pulses_until_div_frequency = div_clock_frequency;
  pulses_until_tima_frequency = current_tima_frequency;
}

void TimerRegisters::pulses(unsigned int pulses) {
  if ((int)(pulses_until_div_frequency - pulses) <= 0) {
    pulses_until_div_frequency = div_frequency - (pulses - pulses_until_div_frequency);
    mem->IncrementDivRegister();
  } else {
    pulses_until_div_frequency -= pulses;
  }
  if (TIMARegisterStart()) {
    if (current_tima_frequency != TIMARegisterFrequency()) {
      current_tima_frequency = TIMARegisterFrequency();
      pulses_until_tima_frequency = current_tima_frequency;
    }
    if ((int)(pulses_until_tima_frequency - pulses) <= 0) {
      pulses_until_tima_frequency = TIMARegisterFrequency() - (pulses - pulses_until_tima_frequency);
      Byte tima = mem->GetInAddr(rTIMA);
      if (tima < 0xff) {
        mem->SetInAddr(rTIMA, tima + 1);
      } else {
        mem->SetInAddr(rTIMA, mem->GetInAddr(rTMA));
        RequestInterrupt(mem, InterruptFlag::TIMER);
      }
    } else {
      pulses_until_tima_frequency -= pulses;
    }
  }
}

bool TimerRegisters::TIMARegisterStart() {
  Byte tac = mem->GetInAddr(rTAC);
  std::bitset<8> tac_bitset(tac);
  return tac_bitset[2];
}

unsigned int TimerRegisters::TIMARegisterFrequency() {
  Byte tac = mem->GetInAddr(rTAC);
  std::bitset<8> tac_bitset(tac);
  switch ((tac_bitset[1] * 2) + tac_bitset[0])
  {
  case (0b00):
    return tac_clock_select_00;
  case (0b01):
    return tac_clock_select_01;
  case (0b10):
    return tac_clock_select_10;
  default:
    return tac_clock_select_11;
  }
}

}