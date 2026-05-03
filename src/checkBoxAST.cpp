#include "../include/checkBox.AST.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_File_Input.H>

checkBoxAST::widgetsToControl checkBoxAST::wtc;

void checkBoxAST::addWidgetsToControl(Fl_File_Input* fileInput, Fl_Button* browse) {
    checkBoxAST::wtc.fileInput = fileInput;
    checkBoxAST::wtc.browse = browse;
}

void checkBoxAST::controlCb(Fl_Widget* widget, void* data) {
    auto* checkButton = static_cast<Fl_Check_Button*>(widget);
    auto* wtc = static_cast<widgetsToControl*>(data);
    if (checkButton->value() != 0) {
        wtc->browse->activate();
        wtc->fileInput->activate();
    }
    else {
        wtc->browse->deactivate();
        wtc->fileInput->deactivate();
    }
}
