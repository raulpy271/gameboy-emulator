
#ifndef UTILS_READ_ROM_H_
#define UTILS_READ_ROM_H_

#include <string>
#include <fstream>

#include "../game/primitives.h"

namespace utils {

bool read_rom_from_file(Byte* rom, std::string file_path);

}

#endif  // UTILS_READ_ROM_H_
