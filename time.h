#pragma once

#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>

class Clock : public Gtk::Window
{

public:
  Clock();
  virtual ~Clock();

protected:

  //Member widgets:
  Gtk::Label m_label;

  sigc::connection conn;
  sigc::connection idk();

  bool updateTime();
  bool on_key_press_event(GdkEventKey* event) override;
};
