#include <iostream>
#include <string>
#include <gtkmm.h>
#include "src/game/game.h"
#include "src/utils/read_rom.h"
#include "src/gui/gameboy_gui.h"

using namespace std;


int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  gameboy::Console game;
  Byte rom_data[32 * 1024];
  string file_path = "roms-example/hello-world.gb";
  utils::read_rom_from_file(rom_data, file_path);
  game.initialize_registers();
  game.load_rom(rom_data);

  while (game.cpu.reg.PC != 0x190) {
    game.run_a_instruction_cycle();
  }

  GameBoyWindow window(&game);

  return app->run(window);
}

