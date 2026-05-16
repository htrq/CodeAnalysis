#include "../include/commandBuilderCT.hpp"
#include <print>
#include <string>

std::string commandBuilderCT::baseTemplate { "clang-tidy " };
std::string commandBuilderCT::optionTemplate { "-checks='-* " };
std::string commandBuilderCT::astOptionTemplate{};
std::string commandBuilderCT::mainFilePathTemplate{};

void commandBuilderCT::addOption(std::string& option, Fl_Text_Buffer& commandBuffer) {
    std::println("Recieved option: {}", option);
    commandBuilderCT::optionTemplate.pop_back();
    commandBuilderCT::optionTemplate.append("," + option + "\'");
}

void commandBuilderCT::addASTPath(std::string& path, char checkBoxValue) {
    astOptionTemplate = "";
    if (checkBoxValue == 0 || path.empty()) {
        return;
    }
    astOptionTemplate.append("-p " + path + " ");
}

void commandBuilderCT::addMainFilePath(std::string& path) {
    if (path.empty()) {
        return;
    }
    mainFilePathTemplate = "";
    mainFilePathTemplate.append(path + " ");
}

void commandBuilderCT::printCommand(Fl_Text_Buffer& commandBuffer) {
    commandBuffer.text("");
    commandBuffer.append(baseTemplate.c_str());
    commandBuffer.append(astOptionTemplate.c_str());
    commandBuffer.append(mainFilePathTemplate.c_str());
    commandBuffer.append(optionTemplate.c_str());
}

void commandBuilderCT::resetCommand() {
    baseTemplate = "clang-tidy ";
    optionTemplate = "-checks='-*";
    astOptionTemplate = "";
    mainFilePathTemplate = "";
}
