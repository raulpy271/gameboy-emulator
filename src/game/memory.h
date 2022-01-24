
#ifndef GAME_MEMORY_H_
#define GAME_MEMORY_H_

#include "primitives.h"

namespace gameboy {

class Memory {
 public:
  Byte GetInAddr(Address add);

  void SetInAddr(Address add, Byte byte_to_insert);

 private:
  Byte cartridge[32 * KB];
};

}

#endif  // GAME_MEMORY_H_