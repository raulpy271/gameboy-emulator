
#ifndef GAME_STAT_H_
#define GAME_STAT_H_

#include "primitives.h"


namespace gameboy {

Byte GetByteToWriteInSTAT(Byte byte_to_write, Byte old_byte);

}

#endif  // GAME_STAT_H_
