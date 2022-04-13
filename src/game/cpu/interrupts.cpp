
#include <bitset>

#include "interrupts.h"
#include "../hardware_registers.h"

namespace gameboy {

void RequestInterrupt(Memory* mem, InterruptFlag interrupt) {
  std::bitset<8> IF_bitset(mem->GetInAddr(rIF));
  IF_bitset.set((std::size_t) interrupt);
  mem->SetInAddr(rIF, IF_bitset.to_ulong());
}

}