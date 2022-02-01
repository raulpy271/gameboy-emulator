
#include "gameboy_gui.h"

GameBoyWindow::GameBoyWindow() {

  set_default_size(200, 200);

  screen_pixbuf = GameBoyWindow::create_pixbuf(100, 100, 2, 2, 255);

  m_connection_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
            &GameBoyWindow::cycle_handler), 1000 );

  screen.set(screen_pixbuf);

  add(screen);

  screen.show();
  show();
}

bool GameBoyWindow::cycle_handler() {
  if (cycle % 2 == 0) {
    screen_pixbuf = GameBoyWindow::create_pixbuf(100, 100, 255, 0, 0);
  } else {
    screen_pixbuf = GameBoyWindow::create_pixbuf(100, 100, 0, 255, 0);
  }
  cycle++;
  screen.set(screen_pixbuf);
  return true;
}

Glib::RefPtr<Gdk::Pixbuf> GameBoyWindow::create_pixbuf(int width, int height, int r, int g, int b) {
  guint8* array_pixel = new guint8[3 * width * height];
  for (int i = 0; i < (3 * width * height) - 3; i += 3) {
    array_pixel[i] = r;
    array_pixel[i + 1] = g;
    array_pixel[i + 2] = b;
  }
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
    array_pixel,
    Gdk::COLORSPACE_RGB,
    false,
    8,
    width,
    height,
    3 * height
  );
  return pixbuf;
}
