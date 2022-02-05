
#ifndef GUI_GAMEBOY_GUI_H_
#define GUI_GAMEBOY_GUI_H_

#include <gtkmm.h>

#include "../game/tile.h"

class GameBoyWindow: public Gtk::Window {
public:
  GameBoyWindow();

private:

  int cycle = 0;

  Gtk::Image screen;

  Glib::RefPtr<Gdk::Pixbuf> screen_pixbuf;

  sigc::connection m_connection_timeout;

  bool cycle_handler();

  Glib::RefPtr<Gdk::Pixbuf> create_pixbuf(int width, int height, int r, int g, int b);

  Glib::RefPtr<Gdk::Pixbuf> create_pixbuf_from_tile(gameboy::Tile* tile); 

};

#endif  // GUI_GAMEBOY_GUI_H_