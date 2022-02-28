
namespace gameboy {

enum class InterruptVector {
  VBLANK = 0x40,
  LCDC = 0x48,
  SERIAL = 0x50,
  TIMER = 0x58,
  HiToLo = 0x60
};

}