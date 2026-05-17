#ifndef COMMAND_BUILDER_CPP_CHECK_HPP_HTRQ
#define COMMAND_BUILDER_CPP_CHECK_HPP_HTRQ
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include "tipTreeCppCheck.hpp"
#include <string>


class CommandBuilderCppCheck {
    std::string command;
    std::string baseCommand;
    std::string enableOption;
    std::string projectOption;

    bool addedEnableOption  { false };
    bool addedProjectOption { false };
    void setAddedEnableOption(bool value);
    void setAddedProjectOption(bool value);
public:
    CommandBuilderCppCheck() : baseCommand("cppcheck"), enableOption("--enable="), projectOption("--project="){};
    void buildCommand();
    void resetCommand();
    void addProject(std::string& option);
    void addEnable(std::string& option);


    void writeCommandToBuffer(Fl_Text_Buffer* buffer) const;
};

struct CommandBuilderCppCheckContext {
    Fl_Text_Buffer* buffer;
    CommandBuilderCppCheck* commandBuilder;
    tipTreeCppCheck* tipTreeCppCheck;
    Fl_File_Input* projectPath;
};



#endif