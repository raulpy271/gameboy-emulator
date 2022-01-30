#include <iostream>
#include <string>
#include <gtkmm.h>
#include "src/game/game.h"

using namespace std;



int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  Gtk::Window window;
  window.set_default_size(200, 200);

  return app->run(window);
}

