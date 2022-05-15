
#include <utility>
#include <bitset>

#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void INC_X_Instruction(Byte* X, Byte* F, Address* PC) {
  if (((*X) & 0xf) == 0xf) {
    utils::set_half_carry_flag(F, true);
  }
  (*X) = (*X) + 1;
  utils::set_subtract_flag(F, false);
  utils::set_zero_flag(F, !((bool)(*X)));
  *PC = (*PC) + 1;
}

void DEC_X_Instruction(Byte* X, Byte* F, Address* PC) {
  if (((*X) & 0xf) == 0) {
    utils::set_half_carry_flag(F, true);
  } else {
    utils::set_half_carry_flag(F, false);
  }
  (*X) = (*X) - 1;
  utils::set_subtract_flag(F, true);
  utils::set_zero_flag(F, !((bool)(*X)));
  *PC = (*PC) + 1;
}

void ADD_X_Y_Instruction(Byte* X, Byte* Y, Byte* F) {
  *F = 0;
  if (*X + *Y > 0xff) {
    utils::set_carry_flag(F, true);
  }
  if (((*X) & 0xf) + ((*Y) & 0xf) > 0xf) {
    utils::set_half_carry_flag(F, true);
  }
  *X = *X + *Y;
  utils::set_zero_flag(F, !((bool)*X));
}

void AND_X_Y_Instruction(Byte* X, Byte* Y, Byte* F, Address* PC) {
  *X = (*X) & (*Y);
  if ((*X) == 0) {
    utils::set_zero_flag(F, true);
  } else {
    utils::set_zero_flag(F, false);
  }
  utils::set_subtract_flag(F, false);
  utils::set_half_carry_flag(F, true);
  utils::set_carry_flag(F, false);
  *PC = (*PC) + 1;
}

void ADD_HL_XY_Instruction(Byte* H, Byte* L, Byte* X, Byte* Y, Byte* F, Address* PC) {
  Address HL = utils::create_address_from_two_bytes(*H, *L);
  Address XY = utils::create_address_from_two_bytes(*X, *Y);
  std::pair<Byte, Byte> new_HL_pair = utils::create_two_bytes_from_address(HL + XY);

  utils::set_subtract_flag(F, false);
  if ((HL + XY) > 0xFFFF) {
    utils::set_carry_flag(F, true);
  } else {
    utils::set_carry_flag(F, false);
  }
  if (((HL & 0x0FFF) + (XY & 0x0FFF)) > 0x0FFF) {
    utils::set_half_carry_flag(F, true);
  } else {
    utils::set_half_carry_flag(F, false);
  }
  *H = new_HL_pair.first;
  *L = new_HL_pair.second;
  *PC = (*PC) + 1;
}

void LD_XX_d16_Instruction(Memory* mem, Address* PC, Byte* higher_byte_reg, Byte* lower_byte_reg) {
  Address lower_byte_addr = (*PC) + 1;
  Address higher_byte_addr = (*PC) + 2;
  Byte lower_byte =  mem->GetInAddr(lower_byte_addr);
  Byte higher_byte = mem->GetInAddr(higher_byte_addr);
  *higher_byte_reg = higher_byte;
  *lower_byte_reg = lower_byte;
  *PC = (*PC) + 3;
}

void LD_X_d8_Instruction(Memory* mem, Address* PC, Byte* X) {
  Address add_of_value = (*PC) + 1;
  Byte value_to_load_in_C = mem->GetInAddr(add_of_value);
  *X = value_to_load_in_C;
}

void BIT_X_A_Instruction(Byte* F, Byte A, Address* PC, int X) {
  bool bit_X_is_one = (bool)(A & (1 << X));
  utils::set_zero_flag(F, !bit_X_is_one);
  utils::set_subtract_flag(F, false);
  utils::set_half_carry_flag(F, true);
}

void ChangeBitValueFromMemory_Instruction(Memory* mem, Byte higher_byte, Byte lower_byte, bool value, int position) {
  Address addr_to_change = utils::create_address_from_two_bytes(higher_byte, lower_byte);
  Byte value_to_change = mem->GetInAddr(addr_to_change);
  std::bitset<8> value_bitset(value_to_change);
  value_bitset.set(position, value);
  mem->SetInAddr(addr_to_change, value_bitset.to_ulong());
}

void PUSH_PC_Instruction(Memory* mem, Address* SP, Address PC) {
  std::pair<Byte, Byte> PC_pair = utils::create_two_bytes_from_address(PC);
  mem->SetInAddr((*SP) - 1, PC_pair.first);
  mem->SetInAddr((*SP) - 2, PC_pair.second);
  (*SP) -= 2;
}

void PUSH_XX_Instruction(Memory* mem, Address* SP, Byte higher_byte, Byte lower_byte, Address* PC) {
  mem->SetInAddr((*SP) - 1, higher_byte);
  mem->SetInAddr((*SP) - 2, lower_byte);
  *SP = (*SP) - 2;
  *PC = (*PC) + 1;
}
void POP_XX_Instruction(Memory* mem, Address* SP, Byte* higher_byte, Byte* lower_byte, Address* PC) {
  *lower_byte = mem->GetInAddr(*SP);
  *higher_byte = mem->GetInAddr((*SP) + 1);
  *SP = (*SP) + 2;
  *PC = (*PC) + 1;
}

void SetSUBFlags(Byte* F, Byte X, Byte Y) {
  *F = 0b01000000;
  Byte X_lower_part = X & 0xf;
  Byte Y_lower_part = Y & 0xf;
  if (X < Y) {
    utils::set_carry_flag(F, true);
  }
  if ((X_lower_part) < (Y_lower_part)) {
    utils::set_half_carry_flag(F, true);
  }
  Byte diff = X - Y;
  utils::set_zero_flag(F, !((bool)diff));
}

}
