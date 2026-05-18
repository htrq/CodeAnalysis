#ifndef COMMAND_BUILDER_ASAN_HPP_HTRQ
#define COMMAND_BUILDER_ASAN_HPP_HTRQ
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include "tipTreeASan.hpp"
#include <string>

//clang++ -g -O0 -fno-omit-frame-pointer -fsanitize=address main.cpp -o app
class CommandBuilderASan {
    std::string command;
    std::string baseCommand;
    std::string fsanitizeOption;
    std::string mainPathOption;
    std::string outputFileOption;

    bool addedFsanitizeOption { false };
    // bool addedProjectOption { false };
    // void setAddedEnableOption(bool value);
    // void setAddedProjectOption(bool value);
public:
    CommandBuilderASan() : baseCommand("clang++ -g -O0 -fno-omit-frame-pointer"), 
    fsanitizeOption("--fsanitize="), outputFileOption("-o"){};
    void buildCommand();
    void resetCommand();
    void addFsanitize(std::string& option);
    void addMainPath(std::string& option);
    void addOutputFileOption(std::string& option);

    void writeCommandToBuffer(Fl_Text_Buffer* buffer) const;
};

struct CommandBuilderASanContext {
    Fl_Text_Buffer* buffer;
    CommandBuilderASan* commandBuilder;
    tipTreeASan* tipTreeASanCheck;
    Fl_Input* compiledNameInput;
    Fl_File_Input* mainFilePath;
};



#endif