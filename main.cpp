#include <iostream>
#include <string>
#include <gtkmm.h>
#include "src/game/game.h"
#include "src/gui/gameboy_gui.h"

using namespace std;


int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  GameBoyWindow window;

  return app->run(window);
}

