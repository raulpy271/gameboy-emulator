
#include "read_rom.h"

namespace utils {

void read_rom_from_file(Byte* rom, std::string file_path) {
  std::fstream rom_file;
  rom_file.open(file_path, std::fstream::in | std::fstream::binary);
  rom_file.read((char *)rom, 32 * 1024);
  rom_file.close();
}

}
