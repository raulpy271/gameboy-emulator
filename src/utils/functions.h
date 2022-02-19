
#include "../game/primitives.h"

namespace utils {

Address create_address_from_two_bytes(Byte higher_byte, Byte lower_byte);

void increment_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg);

void decrement_registers_pair(Byte* higher_byte_reg, Byte* lower_byte_reg);

unsigned int integer_division(unsigned int n, unsigned int d);


}