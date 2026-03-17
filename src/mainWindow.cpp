#include "../include/mainWindow.hpp"
#include "../include/widgetData.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Terminal.H>
#include <print>


void mainWindow::createWindow() {
  auto* window = new Fl_Double_Window(612, 230, 763, 503);
  
  auto* tabs = new Fl_Tabs(19, 27, 716, 267);
  {
    auto* group1 = new Fl_Group(25, 69, 714, 216);
    group1->color(FL_RED);
    group1->end(); 
    auto* group2 = new Fl_Group(25, 69, 714, 216);
    group2->color(FL_YELLOW);
    group2->end();
    auto* group3 = new Fl_Group(25, 69, 714, 216);
    group3->color(FL_GREEN);
    group3->end();

    auto* pages = new widgetData::tabsPages(tabs, group1, group2, group3);
  }
    tabs->end();
  
  auto* groupTerminal = new Fl_Group(18, 302, 721, 196);
  {
    auto* terminal = new Fl_Terminal(22, 303, 716, 192);
  }
  groupTerminal->end();

  window->end();
  window->show();
}

void mainWindow::changeTabCallback(Fl_Widget* widget, void* data) {
  auto* tabs = static_cast<Fl_Tabs*>(widget);
  auto* pages = static_cast<widgetData::tabsPages*>(data);

  switch (pages->getIndex()) {
  case 1:
    pages->setGroup(1);
    break;
  case 2:
    pages->setGroup(2);
    break;
  case 3:
    pages->setGroup(3);
    break;
  default:
    std::println("Error in switch statement");
    break;
  }
}