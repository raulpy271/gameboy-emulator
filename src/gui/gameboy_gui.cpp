
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
  add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);

  screen.show();
  show();
}

bool GameBoyWindow::draw_screen_handler() {
  game->RunAFrameAndExecuteInstructions();
  screen_pixbuf = GameBoyWindow::create_pixbuf_from_ppu_data();
  screen.set(screen_pixbuf->scale_simple(SCREEN_X_SIZE * 2, SCREEN_Y_SIZE * 2, (Gdk::InterpType) 0 ));
  return true;
}

bool GameBoyWindow::on_key_press_event(GdkEventKey* key_event) {
  switch (key_event->keyval)
  {
  case BOTTON_ARROW_DOWN: {
      std::cout << "Setinha baixo" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Down, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_ARROW_UP: {
      std::cout << "Setinha cima" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_ARROW_RIGHT: {
      std::cout << "Setinha direita" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Right, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_ARROW_LEFT: {
      std::cout << "Setinha esquerda" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Left, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_B: {
      std::cout << "Botão B" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::B, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_A: {
      std::cout << "Botão A" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_SELECT: {
      std::cout << "Botão SELECT" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Select, gameboy::BottonEventType::PRESS);
      return true;
    }
  case BOTTON_START: {
      std::cout << "Botão START" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Start, gameboy::BottonEventType::PRESS);
      return true;
    }
  default:
    break;
  }
  std::cout << "Non mapped botton" << std::endl;
  std::cout << "Keyval: " << key_event->keyval << std::endl;
  std::cout << "State: " << key_event->state << std::endl;
  return false;
}

bool GameBoyWindow::on_key_release_event(GdkEventKey* key_event) {
  switch (key_event->keyval)
  {
  case BOTTON_ARROW_DOWN: {
      std::cout << "Setinha baixo (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Down, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_ARROW_UP: {
      std::cout << "Setinha cima (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Up, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_ARROW_RIGHT: {
      std::cout << "Setinha direita (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Right, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_ARROW_LEFT: {
      std::cout << "Setinha esquerda (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Left, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_B: {
      std::cout << "Botão B (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::B, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_A: {
      std::cout << "Botão A (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::A, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_SELECT: {
      std::cout << "Botão SELECT (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Select, gameboy::BottonEventType::RELEASE);
      return true;
    }
  case BOTTON_START: {
      std::cout << "Botão START (release)" << std::endl;
      game->HandleBottonEvent(gameboy::Botton::Start, gameboy::BottonEventType::RELEASE);
      return true;
    }
  default:
    break;
  }
  std::cout << "Non mapped botton (release)" << std::endl;
  std::cout << "Keyval: " << key_event->keyval << std::endl;
  std::cout << "State: " << key_event->state << std::endl;
  return false;
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
