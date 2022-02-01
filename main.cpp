#include <iostream>
#include <string>
#include <gtkmm.h>
#include "src/game/game.h"

using namespace std;

Glib::RefPtr<Gdk::Pixbuf> create_pixbuf(int width, int height) {
  guint8* array_pixel = new guint8[3 * width * height];
  for (int i = 0; i < (3 * width * height) - 3; i += 3) {
    array_pixel[i] = 255;
    array_pixel[i + 1] = 255;
    array_pixel[i + 2] = 255;
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


int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  Gtk::Window window;
  window.set_default_size(200, 200);


  Glib::RefPtr<Gdk::Pixbuf> pixbuf = create_pixbuf(100, 100);
  Gtk::Image image(pixbuf);

  window.add(image);

  image.show();
  window.show();

  return app->run(window);
}

