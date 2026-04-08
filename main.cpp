#define FL_OVERRIDE                                                            \
  override // old fltk versions may put FL_OVERRIDE instead of normal override
#include "include/mainWindow.hpp"
#include <Fl/Fl.H>
#include <Fl/Fl_Double_Window.H>
#include <print>

int main() {
  std::println("Hello world");
  mainWindow::createWindow();

  return Fl::run();
}
