#ifndef MAIN_WINDOW_HTRQ_HPP
#define MAIN_WINDOW_HTRQ_HPP

#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>

class mainWindow {
  static void changeTabCallback(Fl_Widget *widget, void *data);

public:
  mainWindow() = default;

  static void createWindow();
};

#endif