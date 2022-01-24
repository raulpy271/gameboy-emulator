
#include "primitives.h"
#include "memory.h"
#include "cpu.h"

namespace gameboy {

class Console {
 public:
  Memory mem;
  CPU cpu;
};

}