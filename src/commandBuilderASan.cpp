#include "../include/commandBuilderASan.hpp"
#include <FL/Fl_Text_Buffer.H>
#include <string>

void CommandBuilderASan::buildCommand() {
    command.clear();
    command.append(baseCommand + ' ' + fsanitizeOption + ' ' + mainPathOption + ' ' + outputFileOption);
}

void CommandBuilderASan::resetCommand() {
    fsanitizeOption = "--fsanitize=";
    addedFsanitizeOption = false;
    mainPathOption = "";
    outputFileOption = "-o";
}

void CommandBuilderASan::addFsanitize(std::string& option) {
    if (!addedFsanitizeOption) {
        fsanitizeOption.append(option);
        addedFsanitizeOption = true;
    }
    else {
        fsanitizeOption.append(',' + option);
    }
}

void CommandBuilderASan::addMainPath(std::string& option) {
    mainPathOption.clear();
    mainPathOption.append(option);
}

void CommandBuilderASan::addOutputFileOption(std::string& option) {
    outputFileOption.clear();
    outputFileOption.append("-o " + option);
}

void CommandBuilderASan::writeCommandToBuffer(Fl_Text_Buffer* buffer) const {
    buffer->text(command.c_str());
}