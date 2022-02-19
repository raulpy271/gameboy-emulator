
#include "gameboy_gui.h"

GameBoyWindow::GameBoyWindow(gameboy::Console* game) {

  this->game = game;

  set_default_size(256, 256);

  m_connection_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this, &GameBoyWindow::cycle_handler), 1000);

  cycle_handler();

  screen.set(screen_pixbuf);

  add(screen);

  screen.show();
  show();
}

bool GameBoyWindow::cycle_handler() {
  game->ppu.UpdateImageData();
  screen_pixbuf = GameBoyWindow::create_pixbuf_from_ppu_data();
  screen.set(screen_pixbuf);
  return true;
}

Glib::RefPtr<Gdk::Pixbuf> GameBoyWindow::create_pixbuf_from_ppu_data() {
  guint8* array_pixel = new guint8[3 * game->ppu.imageSize];
  int next_pos = 0;
  for (int i = 0; i < game->ppu.imageSize; i++) {
    array_pixel[next_pos    ] = 80 * game->ppu.imageData[i];
    array_pixel[next_pos + 1] = 80 * game->ppu.imageData[i];
    array_pixel[next_pos + 2] = 80 * game->ppu.imageData[i];
    next_pos += 3;
  }
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
    array_pixel,
    Gdk::COLORSPACE_RGB,
    false,
    8,
    256,
    256,
    3 * 256 
  );
  return pixbuf;
}
