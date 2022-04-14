
#ifndef GUI_GAMEBOY_GUI_H_
#define GUI_GAMEBOY_GUI_H_

#include <gtkmm.h>

#include "../game/tile.h"
#include "../game/game.h"
#include "../game/primitives.h"

class GameBoyWindow: public Gtk::Window {
public:
  GameBoyWindow(gameboy::Console* game);

private:

  gameboy::Console* game;

  int cycle = 0;

  Gtk::Image screen;

  Glib::RefPtr<Gdk::Pixbuf> screen_pixbuf;

  sigc::connection draw_screen_connection;

  bool draw_screen_handler();

  bool on_key_press_event(GdkEventKey* event) override;

  Glib::RefPtr<Gdk::Pixbuf> create_pixbuf_from_ppu_data();

  guint8 color_number_to_pixel_channel(ColorNumber color);

};

#endif  // GUI_GAMEBOY_GUI_H_