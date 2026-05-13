#ifndef COMMAND_BUILDER_CLANG_TIDY_HPP_HTRQ
#define COMMAND_BUILDER_CLANG_TIDY_HPP_HTRQ
#include <FL/Fl_File_Input.H>
#include <string>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Check_Button.H>
#include <Fl/Fl_Text_Display.H>
#include "../include/tipTree.hpp"

struct commandBuilderCLContext {
    Fl_Text_Buffer* commandBuffer;
    Fl_Check_Button* astButton;
    tipTree* tree;
    Fl_File_Input* astPath;
};

class commandBuilderCT {
    
public:
    static std::string baseTemplate;
    static std::string optionTemplate;
    static std::string astOptionTemplate;
    static void addOption(std::string& option, Fl_Text_Buffer& commandBuffer);
    static void addASTPath(std::string& path, char checkBoxValue);
    static void printCommand(Fl_Text_Buffer& commandBuffer);
    static void resetCommandLine(Fl_Text_Buffer& commandBuffer);
};


#endif