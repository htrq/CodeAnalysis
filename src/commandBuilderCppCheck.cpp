#include "commandBuilderCppCheck.hpp"
#include <FL/Fl_Text_Buffer.H>
#include <string>


void CommandBuilderCppCheck::buildCommand() {
    command.clear();
    command.append(baseCommand + ' ');
    if (addedProjectOption) {
        command.append(projectOption + ' ');
    }
    if (addedEnableOption) {
        command.append(enableOption);
    }
}

void CommandBuilderCppCheck::resetCommand() {
    command.clear();
    baseCommand = "cppcheck";
    projectOption = "--project=";
    enableOption = "--enable=";
    setAddedProjectOption(false);
    setAddedEnableOption(false);
}

void CommandBuilderCppCheck::setAddedEnableOption(bool value) {
    addedEnableOption = value;
}

void CommandBuilderCppCheck::setAddedProjectOption(bool value) {
    addedProjectOption = value;
}

void CommandBuilderCppCheck::addProject(std::string& option) {
    if (option.empty()) {
        return;
    }
    if (!addedProjectOption) {
        projectOption.append(option );
        setAddedProjectOption(true);
    }
    else {
        projectOption.clear();
        projectOption.append("--project " + option);
        setAddedProjectOption(true);
    }
}

void CommandBuilderCppCheck::addEnable(std::string& option) {
    if (option.empty()) {
        return;
    }
    if (addedEnableOption) {
        enableOption.append(',' + option);
    }
    else {
        enableOption.append(option );
        setAddedEnableOption(true);
    }
}

void CommandBuilderCppCheck::writeCommandToBuffer(Fl_Text_Buffer* buffer) const {
    buffer->text(command.c_str());
}
