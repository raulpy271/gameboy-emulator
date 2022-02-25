
#include <bitset>

#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::RES_7_aHL_Instruction(Memory* mem) {
  Address higher_byte = reg.H;
  Address lower_byte = reg.L;
  Address addr_to_reset = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  Byte value_to_reset = mem->GetInAddr(addr_to_reset);
  std::bitset<8> value(value_to_reset);
  value.reset(7);
  mem->SetInAddr(addr_to_reset, value.to_ulong());
  reg.PC += 2;
}

void CPU::SET_7_aHL_Instruction(Memory* mem) {
  Address higher_byte = reg.H;
  Address lower_byte = reg.L;
  Address addr_to_reset = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  Byte value_to_reset = mem->GetInAddr(addr_to_reset);
  std::bitset<8> value(value_to_reset);
  value.set(7);
  mem->SetInAddr(addr_to_reset, value.to_ulong());
  reg.PC += 2;
}

}