#ifndef CHECK_BOX_HPP_HTRQ
#define CHECK_BOX_HPP_HTRQ
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Widget.H>


class checkBoxAST : public Fl_Check_Button {

struct widgetsToControl {
  Fl_File_Input *fileInput;
  Fl_Button *browse;
};



public:
  static widgetsToControl wtc;
  using Fl_Check_Button::Fl_Check_Button;
  static void addWidgetsToControl(Fl_File_Input *fileInput, Fl_Button *browse);
  static void controlCb(Fl_Widget* widget, void* data);
};

#endif