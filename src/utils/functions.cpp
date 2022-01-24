
#include "../game/primitives.h"
#include "functions.h"

namespace utils {

Address create_address_from_two_bytes(Byte higher_byte, Byte lower_byte) {
  return (higher_byte * 0x100) + lower_byte;
}

}