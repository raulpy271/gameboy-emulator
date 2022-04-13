
#include <iostream>

#include "gameboy_gui.h"
#include "../game/hardware_definitions.h"
#include "gui_definitions.h"
#include "../game/hardware_registers.h"
#include "../game/cpu/interrupts.h"

GameBoyWindow::GameBoyWindow(gameboy::Console* game) {

  this->game = game;

  set_default_size(SCREEN_X_SIZE, SCREEN_Y_SIZE);

  sigc::slot<bool()> draw_screen_ptr = sigc::mem_fun(*this, &GameBoyWindow::draw_screen_handler);

  draw_screen_connection = Glib::signal_timeout().connect(draw_screen_ptr, INTERVAL_TO_RENDER_FRAME_IN_MS);

  screen.set(screen_pixbuf);

  add(screen);

  screen.show();
  show();
}

bool GameBoyWindow::draw_screen_handler() {
  for (int i = 0; i < INSTRUCTION_BETWEEN_EACH_FRAME; i++) {
    game->run_a_instruction_cycle();
  }
  game->ppu.UpdateImageData();
  screen_pixbuf = GameBoyWindow::create_pixbuf_from_ppu_data();
  RequestInterrupt(&(game->mem), gameboy::InterruptFlag::VBLANK);
  screen.set(screen_pixbuf->scale_simple(SCREEN_X_SIZE * 2, SCREEN_Y_SIZE * 2, (Gdk::InterpType) 0 ));
  return true;
}

Glib::RefPtr<Gdk::Pixbuf> GameBoyWindow::create_pixbuf_from_ppu_data() {
  guint8* array_pixel = new guint8[3 * SCREEN_X_SIZE * SCREEN_Y_SIZE];
  int next_pos = 0;
  for (int i = 0; i < SCREEN_X_SIZE * SCREEN_Y_SIZE; i++) {
    array_pixel[next_pos    ] = color_number_to_pixel_channel(game->ppu.screen[i]);
    array_pixel[next_pos + 1] = color_number_to_pixel_channel(game->ppu.screen[i]);
    array_pixel[next_pos + 2] = color_number_to_pixel_channel(game->ppu.screen[i]);
    next_pos += 3;
  }
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
    array_pixel,
    Gdk::COLORSPACE_RGB,
    false,
    8,
    SCREEN_X_SIZE,
    SCREEN_Y_SIZE,
    3 * SCREEN_X_SIZE
  );
  return pixbuf;
}

guint8 GameBoyWindow::color_number_to_pixel_channel(ColorNumber color) {
  switch (color)
  {
  case 0:
    return 0xff;
  case 1:
    return 0xA0;
  case 2:
    return 0x50;
  case 3:
    return 0x00;
  default:
    throw "Not a color number";
  }
}
