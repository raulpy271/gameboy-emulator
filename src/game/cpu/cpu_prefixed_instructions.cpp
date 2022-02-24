
#include "cpu.h"
#include "cpu_utils.h"
#include "../../utils/functions.h"
#include "../../utils/register_F_manipulate.h"

namespace gameboy {

void CPU::RES_7_aHL_Instruction(Memory* mem) {
  // TODO
  reg.PC += 3;
}

}