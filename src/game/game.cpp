
#include "game.h"
#include "hardware_registers.h"
#include "hardware_definitions.h"
#include "emulator_definitions.h"
#include "LCDC.h"
#include "cpu/interrupts.h"

namespace gameboy {

Console::Console() : 
  timer(&mem, DIV_FREQUENCY_Hz, TAC_FREQUENCY_00_Hz, TAC_FREQUENCY_01_Hz, TAC_FREQUENCY_10_Hz, TAC_FREQUENCY_11_Hz),
  ppu(&mem) {}

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

  mem.SetInAddr(rP1 , 0xCF);
  mem.SetInAddr(rSB , 0x00);
  mem.SetInAddr(rSC , 0x7E);
  mem.SetInAddr(rDIV , 0xAB);
  mem.SetInAddr(rTIMA , 0x00);
  mem.SetInAddr(rTMA , 0x00);
  mem.SetInAddr(rTAC , 0xF8);
  mem.SetInAddr(rIF , 0xE1);
  mem.SetInAddr(rNR10 , 0x80);
  mem.SetInAddr(rNR11 , 0xBF);
  mem.SetInAddr(rNR12 , 0xF3);
  mem.SetInAddr(rNR13 , 0xFF);
  mem.SetInAddr(rNR14 , 0xBF);
  mem.SetInAddr(rNR21 , 0x3F);
  mem.SetInAddr(rNR22 , 0x00);
  mem.SetInAddr(rNR23 , 0xFF);
  mem.SetInAddr(rNR24 , 0xBF);
  mem.SetInAddr(rNR30 , 0x7F);
  mem.SetInAddr(rNR31 , 0xFF);
  mem.SetInAddr(rNR32 , 0x9F);
  mem.SetInAddr(rNR33 , 0xFF);
  mem.SetInAddr(rNR34 , 0xBF);
  mem.SetInAddr(rNR41 , 0xFF);
  mem.SetInAddr(rNR42 , 0x00);
  mem.SetInAddr(rNR43 , 0x00);
  mem.SetInAddr(rNR44 , 0xBF);
  mem.SetInAddr(rNR50 , 0x77);
  mem.SetInAddr(rNR51 , 0xF3);
  mem.SetInAddr(rNR52 , 0xF1);
  mem.SetInAddr(rLCDC , 0x91);
  mem.SetInAddr(rSCY , 0x00);
  mem.SetInAddr(rSCX , 0x00);
  mem.SetInAddr(rLY , 0x00);
  mem.SetInAddr(rLYC , 0x00);
  mem.SetInAddr(rBGP , 0xFC);
  mem.SetInAddr(rOBP0 , 0x0);
  mem.SetInAddr(rOBP1 , 0x0);
  mem.SetInAddr(rWY , 0x00);
  mem.SetInAddr(rWX , 0x00);
  mem.SetInAddr(rKEY1 , 0xFF);
  mem.SetInAddr(rVBK , 0xFF);
  mem.SetInAddr(rHDMA1 , 0xFF);
  mem.SetInAddr(rHDMA2 , 0xFF);
  mem.SetInAddr(rHDMA3 , 0xFF);
  mem.SetInAddr(rHDMA4 , 0xFF);
  mem.SetInAddr(rHDMA5 , 0xFF);
  mem.SetInAddr(rRP , 0xFF);
  mem.SetInAddr(rBCPS , 0xFF);
  mem.SetInAddr(rBCPD , 0xFF);
  mem.SetInAddr(rOCPS , 0xFF);
  mem.SetInAddr(rOCPD , 0xFF);
  mem.SetInAddr(rSVBK , 0xFF);
  mem.SetInAddr(rIE , 0x00);
}

void Console::run_a_instruction_cycle() {
  timer.pulses(MEAN_OF_PULSES_BY_INSTRUCTION);
  InterruptFlag interrupt = cpu.GetNextInterrupt(&mem);
  if (interrupt == InterruptFlag::NoInterrupt) {
    cpu.execute_intruction(&mem);
  } else {
    cpu.execute_interrupt(&mem, interrupt);
  }
}

void Console::HandleBottonEvent(Botton botton, BottonEventType type) {
  if (type == BottonEventType::PRESS) {
    mem.keypad.PressBotton(botton);
  } else {
    mem.keypad.ReleaseBotton(botton);
  }
  RequestInterrupt(&mem, InterruptFlag::HiToLo);
}

void Console::RunAFrameAndExecuteInstructions() {
  int i;
  mem.SetInAddr(rLY, 0);
  bool lcd_enable = LCDEnable(mem.GetInAddr(rLCDC));
  if (lcd_enable) {
    for (int LY = 0; LY <= MAX_LY; LY++) {
      ScanLineAndSTATInterruptions();
      for (i = 0; i < INSTRUCTIONS_BY_EACH_SCANLINE; i++) {
        run_a_instruction_cycle();
      }
    }
  } else {
    for (i = 0; i < (SCREEN_X_SIZE * SCREEN_Y_SIZE); i++) {
      ppu.screen[i] = 0;
    }
    for (i = 0; i < INSTRUCTIONS_BY_EACH_FRAME; i++) {
      run_a_instruction_cycle();
    }
  }
}

void Console::ScanLineAndSTATInterruptions() {
  Byte ly;
  ly = mem.GetInAddr(rLY);
  if (ly == mem.GetInAddr(rLYC)) {
    mem.SetCoincidenceFlagLYEqualLYC(true);
  } else {
    mem.SetCoincidenceFlagLYEqualLYC(false);
  }
  if (ly < SCREEN_Y_SIZE) {
    ppu.ScanLine();
  }
  if (ly == SCREEN_Y_SIZE) {
    RequestInterrupt(&mem, InterruptFlag::VBLANK);
  }
  mem.SetInAddr(rLY, ly + 1);
}

}