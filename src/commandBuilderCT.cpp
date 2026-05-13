#include "../include/commandBuilderCT.hpp"
#include <print>
#include <string>

std::string commandBuilderCT::baseTemplate { "clang-tidy " };
std::string commandBuilderCT::optionTemplate { "-checks='-* " };
std::string commandBuilderCT::astOptionTemplate {};

void commandBuilderCT::addOption(std::string& option, Fl_Text_Buffer& commandBuffer) {
    std::println("Recieved option: {}", option);
    commandBuilderCT::optionTemplate.pop_back();
    commandBuilderCT::optionTemplate.append("," + option + "\'");
}

void commandBuilderCT::addASTPath(std::string& path, char checkBoxValue) {
    if (checkBoxValue == 0) {
        return;
    }
    astOptionTemplate.append(path);
    baseTemplate.append(astOptionTemplate);
}

void commandBuilderCT::printCommand(Fl_Text_Buffer& commandBuffer) {
    commandBuffer.text("");
    commandBuffer.append(baseTemplate.c_str());
    commandBuffer.append(optionTemplate.c_str());
    commandBuffer.append(astOptionTemplate.c_str());
}

void commandBuilderCT::resetCommandLine(Fl_Text_Buffer& commandBuffer) {
    baseTemplate = "clang-tidy ";
    optionTemplate = "-checks='-*";
    astOptionTemplate = " -p ";
    commandBuffer.replace(0, commandBuffer.length(), baseTemplate.c_str());
}
