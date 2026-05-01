#include "../include/mainWindow.hpp"
#include "../include/linuxTerminal.hpp"
#include "../include/widgetData.hpp"
#include "../include/tipTree.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Terminal.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Wizard.H>
#include <FL/fl_config.h>
#include <clocale>
#include <print>

void mainWindow::createWindow() {
  Fl::set_font(FL_HELVETICA, "DejaVu Sans");
  std::println("font name: {}",Fl::get_font_name(FL_HELVETICA));

  auto *window = new Fl_Double_Window(612, 230, 763, 503, "окно");

  auto *tabs = new Fl_Tabs(19, 27, 716, 267);
  {
    auto *group1 = new Fl_Group(25, 69, 714, 216);
    group1->label("clang-tidy");
    group1->labelfont(14);
    
    auto *tree = new tipTree(35, 130, 655, 108);
    tree->begin();
    tree->initTipTree();
    tree->callback(tipTree::treeCb);
    tree->selectmode(FL_TREE_SELECT_MULTI);
    tree->root_label("sections");
    
    tree->add("bugprone/assert-side-effect");
    tree->add("bugprone/copy-constructor-init");
    tree->add("bugprone/infinite-loop");
    tree->add("bugprone/use-after-move");
    tree->add("bugprone/sizeof-expression");
    tree->add("bugprone/suspicious-missing-comma");
    tree->add("bugprone/virtual-near-miss");

    tree->add("modernize/use-nullptr");
    tree->add("modernize/use-override");
    tree->add("modernize/loop-convert");
    tree->add("modernize/make-unique");
    tree->add("modernize/make-shared");
    tree->add("modernize/use-auto");
    tree->add("modernize/use-emplace");
    tree->add("bugprone/assert-side-effect");
    tree->add("bugprone/copy-constructor-init");
    tree->add("bugprone/infinite-loop");
    tree->add("bugprone/use-after-move");
    tree->add("bugprone/sizeof-expression");
    tree->add("bugprone/suspicious-missing-comma");
    tree->add("bugprone/virtual-near-miss");

    tree->add("modernize/use-nullptr");
    tree->add("modernize/use-override");
    tree->add("modernize/loop-convert");
    tree->add("modernize/make-unique");
    tree->add("modernize/make-shared");
    tree->add("modernize/use-auto");
    tree->add("modernize/use-emplace");

    tree->add("readability/braces-around-statements");
    tree->add("readability/identifier-naming");
    tree->add("readability/function-size");
    tree->add("readability/magic-numbers");
    tree->add("readability/uppercase-literal-suffix");

    tree->add("performance/for-range-copy");
    tree->add("performance/move-const-arg");
    tree->add("performance/unnecessary-copy-initialization");
    tree->add("performance/inefficient-string-concatenation");
    
    tree->add("cppcoreguidelines/owning-memory");
    tree->add("cppcoreguidelines/pro-type-cstyle-cast");
    tree->add("cppcoreguidelines/special-member-functions");
    tree->add("cppcoreguidelines/avoid-goto");
    
    tree->add("misc/definitions-in-headers");
    tree->add("misc/unused-parameters");
    tree->add("misc/non-private-member-variables-in-classes");
    tree->add("misc/throw-by-value-catch-by-reference");
    std::println("Tree created!");

    tree->end();
    

    
    auto *fileInput = new Fl_File_Input(66, 83, 506, 32);
    fileInput->label("file:");

    auto* browseButton = new Fl_Button(590, 87, 100, 28);
    browseButton->label("browse..");

    group1->end();
    auto *group2 = new Fl_Group(25, 69, 714, 216);
    group2->color(FL_YELLOW);
    group2->end();
    auto *group3 = new Fl_Group(25, 69, 714, 216);
    group3->color(FL_GREEN);
    group3->end();

    auto *pages = new widgetData::tabsPages(tabs, group1, group2, group3);
  }
  tabs->end();

  auto *groupTerminal = new Fl_Group(18, 302, 721, 196);
  {

    auto *term = new linuxTerminal(22, 303, 716, 192);
    term->enterFirstPromt();
    term->createPTY();
    
    //windows terminal
  }
  groupTerminal->end();

  

  window->end();
  window->show();
}

void mainWindow::changeTabCallback(Fl_Widget *widget, void *data) {
  auto *tabs = static_cast<Fl_Tabs *>(widget);// наверное убрать потом
  auto *pages = static_cast<widgetData::tabsPages *>(data);

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
