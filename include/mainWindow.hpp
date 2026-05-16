#ifndef MAIN_WINDOW_HTRQ_HPP
#define MAIN_WINDOW_HTRQ_HPP

#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Text_Buffer.H>
#include "../include/linuxTerminal.hpp"


struct enterCommandContext {
    Fl_Text_Buffer* buffer;
    linuxTerminal* term;
};

class mainWindow {
  static void changeTabCallback(Fl_Widget *widget, void *data);
  enterCommandContext enterCommandCtx;

public:
  mainWindow() = default;

  void createWindow();
};

#endif