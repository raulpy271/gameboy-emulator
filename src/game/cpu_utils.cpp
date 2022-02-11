
#include "cpu_utils.h"

namespace gameboy {

void LD_XX_d16_Instruction(Memory* mem, Address* PC, Byte* higher_byte_reg, Byte* lower_byte_reg) {
  Address lower_byte_addr = (*PC) + 1;
  Address higher_byte_addr = (*PC) + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  *higher_byte_reg = higher_byte;
  *lower_byte_reg = lower_byte;
  *PC = (*PC) + 3;
}

}
