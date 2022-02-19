
#ifndef GUI_GAMEBOY_GUI_H_
#define GUI_GAMEBOY_GUI_H_

#include <gtkmm.h>

#include "../game/tile.h"
#include "../game/game.h"

class GameBoyWindow: public Gtk::Window {
public:
  GameBoyWindow(gameboy::Console* game);

private:

  gameboy::Console* game;

  int cycle = 0;

  Gtk::Image screen;

  Glib::RefPtr<Gdk::Pixbuf> screen_pixbuf;

  sigc::connection m_connection_timeout;

  bool cycle_handler();

  Glib::RefPtr<Gdk::Pixbuf> create_pixbuf_from_ppu_data();

};

#endif  // GUI_GAMEBOY_GUI_H_