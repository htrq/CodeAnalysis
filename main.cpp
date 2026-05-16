#define FL_OVERRIDE                                                            \
  override // old fltk versions may put FL_OVERRIDE instead of normal override
#include "include/mainWindow.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <print>

int main() {
  std::println("Hello world");
  auto* window = new mainWindow();
  window->createWindow();

  return Fl::run();
}
