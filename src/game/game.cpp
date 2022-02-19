
#include "game.h"
#include "hardware_registers.h"

namespace gameboy {

Console::Console() {
  ppu.SetMemory(&mem);
}

void Console::initialize_registers() {
  cpu.reg.PC = 0x0100;
  cpu.reg.SP = 0xfffe;
  cpu.reg.A  = 0x01;
  cpu.reg.F  = 0b11000000;
  cpu.reg.B  = 0x0;
  cpu.reg.C  = 0x13;
  cpu.reg.D  = 0x0;
  cpu.reg.E  = 0xD8;
  cpu.reg.H  = 0x01;
  cpu.reg.L  = 0x4D;

  mem.SetInAddr(P1 , 0xCF);
  mem.SetInAddr(SB , 0x00);
  mem.SetInAddr(SC , 0x7E);
  mem.SetInAddr(DIV , 0xAB);
  mem.SetInAddr(TIMA , 0x00);
  mem.SetInAddr(TMA , 0x00);
  mem.SetInAddr(TAC , 0xF8);
  mem.SetInAddr(IF , 0xE1);
  mem.SetInAddr(NR10 , 0x80);
  mem.SetInAddr(NR11 , 0xBF);
  mem.SetInAddr(NR12 , 0xF3);
  mem.SetInAddr(NR13 , 0xFF);
  mem.SetInAddr(NR14 , 0xBF);
  mem.SetInAddr(NR21 , 0x3F);
  mem.SetInAddr(NR22 , 0x00);
  mem.SetInAddr(NR23 , 0xFF);
  mem.SetInAddr(NR24 , 0xBF);
  mem.SetInAddr(NR30 , 0x7F);
  mem.SetInAddr(NR31 , 0xFF);
  mem.SetInAddr(NR32 , 0x9F);
  mem.SetInAddr(NR33 , 0xFF);
  mem.SetInAddr(NR34 , 0xBF);
  mem.SetInAddr(NR41 , 0xFF);
  mem.SetInAddr(NR42 , 0x00);
  mem.SetInAddr(NR43 , 0x00);
  mem.SetInAddr(NR44 , 0xBF);
  mem.SetInAddr(NR50 , 0x77);
  mem.SetInAddr(NR51 , 0xF3);
  mem.SetInAddr(NR52 , 0xF1);
  mem.SetInAddr(LCDC , 0x91);
  mem.SetInAddr(STAT , 0x85);
  mem.SetInAddr(SCY , 0x00);
  mem.SetInAddr(SCX , 0x00);
  mem.SetInAddr(LY , 0x00);
  mem.SetInAddr(LYC , 0x00);
  mem.SetInAddr(DMA , 0xFF);
  mem.SetInAddr(BGP , 0xFC);
  mem.SetInAddr(OBP0 , 0x0);
  mem.SetInAddr(OBP1 , 0x0);
  mem.SetInAddr(WY , 0x00);
  mem.SetInAddr(WX , 0x00);
  mem.SetInAddr(KEY1 , 0xFF);
  mem.SetInAddr(VBK , 0xFF);
  mem.SetInAddr(HDMA1 , 0xFF);
  mem.SetInAddr(HDMA2 , 0xFF);
  mem.SetInAddr(HDMA3 , 0xFF);
  mem.SetInAddr(HDMA4 , 0xFF);
  mem.SetInAddr(HDMA5 , 0xFF);
  mem.SetInAddr(RP , 0xFF);
  mem.SetInAddr(BCPS , 0xFF);
  mem.SetInAddr(BCPD , 0xFF);
  mem.SetInAddr(OCPS , 0xFF);
  mem.SetInAddr(OCPD , 0xFF);
  mem.SetInAddr(SVBK , 0xFF);
  mem.SetInAddr(IE , 0x00);
}

void Console::run_a_instruction_cycle() {
  cpu.execute_intruction(&mem);
}

void Console::load_rom(Byte* rom) {
  for (int i = 0; i < (32 * 1024); i++) {
    mem.SetInAddr(i, rom[i]);
  }
}

}