
#ifndef UTILS_FUNCTIONS_H_
#define UTILS_FUNCTIONS_H_

#include <utility>

#include "../game/primitives.h"
#include "../game/cpu/interrupts.h"

namespace utils {

Address create_address_from_two_bytes(Byte higher_byte, Byte lower_byte);

std::pair<Byte, Byte> create_two_bytes_from_address(Address addr);

void increment_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg);

void decrement_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg);

unsigned int integer_division(unsigned int n, unsigned int d);

Address GetInterruptHandlingAddress(gameboy::InterruptFlag interrupt);

}

#endif  // UTILS_FUNCTIONS_H_