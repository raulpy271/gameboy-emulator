
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
    Byte tiledata[16] =
    { 
      0x00,0x7e, 0x2a,0x7e, 0xd5,0x7e, 0x2a,0x7e, 0x54,0x7e, 0xff,0x00, 0xff,0x00, 0x00,0x00 
    };
    gameboy::Tile* tile = gameboy::Tile::create_tile(&(tiledata[0]));
    screen_pixbuf = GameBoyWindow::create_pixbuf_from_tile(tile);
    screen_pixbuf = screen_pixbuf->scale_simple(100, 100, Gdk::InterpType::INTERP_NEAREST);
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

Glib::RefPtr<Gdk::Pixbuf>  GameBoyWindow::create_pixbuf_from_tile(gameboy::Tile* tile) {
  guint8* array_pixel = new guint8[3 * 8 * 8];
  int next_pos = 0;
  for (int i = 0; i < (8*8); i++) {
    array_pixel[next_pos]     = tile->data[i] * 80;
    array_pixel[next_pos + 1] = tile->data[i] * 80;
    array_pixel[next_pos + 2] = tile->data[i] * 80;
    next_pos += 3;
  }
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
    array_pixel,
    Gdk::COLORSPACE_RGB,
    false,
    8,
    8,
    8,
    3 * 8
  );
  return pixbuf;

} 