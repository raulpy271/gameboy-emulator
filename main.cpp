#include <iostream>
#include <string>
#include <gtkmm.h>
#include "src/game/game.h"
#include "src/utils/read_rom.h"
#include "src/gui/gameboy_gui.h"

#define INVALID_ARG_EXIT_CODE 128

using namespace std;


int main(int argc, char *argv[])
{
  Byte rom_data[32 * 1024];
  if (argc >= 2 && utils::read_rom_from_file(rom_data, argv[1])) {
    auto app = Gtk::Application::create("org.gameboy-emulator.base");
    gameboy::Console game;
    game.initialize_registers();
    game.mem.load_rom(rom_data);
    GameBoyWindow window(&game);
    return app->run(window);
  } else {
    std::cout << "The argument is not a valid path or the file don't exists." << std::endl;
    return INVALID_ARG_EXIT_CODE;
  }

}

