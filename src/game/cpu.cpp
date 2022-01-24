
#include "cpu.h"
#include "../utils/functions.h"

namespace gameboy {

void CPU::execute_intruction(Memory mem) {
  Byte opcode = mem.GetInAddr(reg.PC);
  switch (opcode)
  {
  case (JP_a16):
    CPU::JP_a16_Instruction(mem);
    break;
  
  default:
    break;
  }
}

void CPU::JP_a16_Instruction(Memory mem) {
  Address lower_byte_addr = reg.PC + 1;
  Address higher_byte_addr = reg.PC + 2;
  Byte lower_byte = mem.GetInAddr(lower_byte_addr);
  Byte higher_byte = mem.GetInAddr(higher_byte_addr);
  Address addr_to_jump = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  reg.PC = addr_to_jump;
}

}