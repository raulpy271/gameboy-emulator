
#include "primitives.h"

namespace gameboy {

class Memory 
{
 private:
  Byte cartridge[32 * KB];

 public:
  Byte GetInAddr(Address add);

  void SetInAddr(Address add, Byte byte_to_insert);
};

}