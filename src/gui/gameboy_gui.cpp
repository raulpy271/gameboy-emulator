
#include "gameboy_gui.h"
#include "../game/hardware_definitions.h"

GameBoyWindow::GameBoyWindow(gameboy::Console* game) {

  this->game = game;

  set_default_size(256, 256);

  sigc::slot<bool()> draw_screen_ptr = sigc::mem_fun(*this, &GameBoyWindow::draw_screen_handler);

  draw_screen_connection = Glib::signal_timeout().connect(draw_screen_ptr, 100);

  screen.set(screen_pixbuf);

  add(screen);

  screen.show();
  show();
}

bool GameBoyWindow::draw_screen_handler() {
  for (int i = 0; i < 2000; i++) {
    game->run_a_instruction_cycle();
  }
  game->ppu.UpdateImageData();
  screen_pixbuf = GameBoyWindow::create_pixbuf_from_ppu_data();
  screen.set(screen_pixbuf);
  return true;
}

Glib::RefPtr<Gdk::Pixbuf> GameBoyWindow::create_pixbuf_from_ppu_data() {
  guint8* array_pixel = new guint8[3 * SCREEN_X_SIZE * SCREEN_Y_SIZE];
  int next_pos = 0;
  for (int i = 0; i < SCREEN_X_SIZE * SCREEN_Y_SIZE; i++) {
    array_pixel[next_pos    ] = 80 * game->ppu.screen[i];
    array_pixel[next_pos + 1] = 80 * game->ppu.screen[i];
    array_pixel[next_pos + 2] = 80 * game->ppu.screen[i];
    next_pos += 3;
  }
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
    array_pixel,
    Gdk::COLORSPACE_RGB,
    false,
    8,
    SCREEN_X_SIZE,
    SCREEN_Y_SIZE,
    3 * SCREEN_Y_SIZE
  );
  return pixbuf;
}
