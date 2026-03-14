#define FL_OVERRIDE override    // old fltk versions may put FL_OVERRIDE instead of normal override
#include <print>
#include <Fl/Fl.H>
#include <Fl/Fl_Double_Window.H>
#include "include/mainWindow.hpp"

int main()
{
    std::println("Hello world");
    mainWindow::createWindow();
    
    return Fl::run();
}