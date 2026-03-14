#include "../include/mainWindow.hpp"
#include "../include/widgetData.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Browser_.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>
#include <print>


void mainWindow::createWindow() {
  auto* window = new Fl_Double_Window(612, 230, 763, 503);
  auto* browser = new Fl_Browser(25, 25, 160, 446);
  browser->type(FL_HOLD_BROWSER);
  browser->add("line1");
  browser->add("line2");
  browser->add("line3");
  auto* wizard = new Fl_Wizard(211, 25, 526, 442);
  {
    auto* group1 = new Fl_Group(211, 25, 526, 442);
    group1->color(FL_RED);
    group1->end();
    auto* group2 = new Fl_Group(211, 25, 526, 442);
    group2->color(FL_YELLOW);
    group2->end();
    auto* group3 = new Fl_Group(211, 25, 526, 442);
    group3->color(FL_GREEN);
    group3->end();

    auto* pages = new widgetData::wizardPages(wizard, group1, group2, group3);
    browser->callback(mainWindow::browserCallback, pages);
  }

  wizard->end();
  window->end();
  window->show();
}

void mainWindow::browserCallback(Fl_Widget *widget, void *data) {
  auto* browser = dynamic_cast<Fl_Browser *>(widget);
  auto* pages = static_cast<widgetData::wizardPages *>(data);

  switch (browser->value()) {
  case 1:
    pages->setGroup1();
    break;
  case 2:
    pages->setGroup2();
    break;
  case 3:
    pages->setGroup3();
    break;
  default:
    std::println("Error in switch statement");
    break;
  }
}