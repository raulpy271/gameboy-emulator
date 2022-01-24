#include <iostream>
#include <string>
#include "src/game/game.h"

using namespace std;

int main()
{
  int t = 10;
  gameboy::Console game;
  game.mem.SetInAddr(0x100, 0xc3);
  game.mem.SetInAddr(0x101, 0x50);
  game.mem.SetInAddr(0x102, 0x01);
  game.mem.SetInAddr(0x150, 0xff);
  cout << game.cpu.reg.PC << endl;
  game.cpu.execute_intruction(game.mem);
  cout << game.cpu.reg.PC << endl;
}
