#include "../include/mainWindow.hpp"
#include "../include/commandBuilderASan.hpp"
#include "../include/commandBuilderCT.hpp"
#include "../include/commandBuilderCppCheck.hpp"
#include "../include/linuxTerminal.hpp"
#include "../include/tipTree.hpp"
#include "../include/tipTreeASan.hpp"
#include "../include/tipTreeCppCheck.hpp"
#include "../include/widgetData.hpp"
#include "checkBox.AST.hpp"
#include "commandBuilderASan.hpp"
#include "tipTreeASan.hpp"
#include "tipTreeCppCheck.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Terminal.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <FL/Fl_Wizard.H>
#include <FL/fl_config.h>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Display.H>
#include <Fl/fl_ask.H>
#include <clocale>
#include <print>
#include <string>

namespace {
void addButtonCb(Fl_Widget *widget, void *data) {
  auto *context = static_cast<commandBuilderCLContext *>(data);
  auto *item = context->tree->callback_item();
  if (item != nullptr) {
    std::string option = item->label();
    std::string astPath = context->astPath->value();
    std::string mainPath = context->mainFilePath->value();
    std::println("label for option is: {}", option);
    Fl_Text_Buffer *buffer = context->commandBuffer;
    commandBuilderCT::addOption(option, *buffer);
    commandBuilderCT::addASTPath(astPath, context->astCheck->value());
    commandBuilderCT::addMainFilePath(mainPath);
    commandBuilderCT::printCommand(*buffer);
  }
}

void clearButtonCb(Fl_Widget *widget, void *data) {
  auto *buffer = static_cast<Fl_Text_Buffer *>(data);
  buffer->text("");
  commandBuilderCT::resetCommand();
}

void addButtonCbCppCheck(Fl_Widget *widget, void *data) {
  auto *context = static_cast<CommandBuilderCppCheckContext *>(data);
  std::string enableOption = context->tipTreeCppCheck->callback_item()->label();
  context->commandBuilder->addEnable(enableOption);
  std::string projectOption = context->projectPath->value();
  context->commandBuilder->addProject(projectOption);
  context->commandBuilder->buildCommand();
  context->commandBuilder->writeCommandToBuffer(context->buffer);
}

void addButtonCbASanCheck(Fl_Widget *widget, void *data) {
  auto *context = static_cast<CommandBuilderASanContext *>(data);
  std::string snanitizeOption =
      context->tipTreeASanCheck->callback_item()->label();
  context->commandBuilder->addFsanitize(snanitizeOption);
  std::string mainPathOption = context->mainFilePath->value();
  context->commandBuilder->addMainPath(mainPathOption);
  std::string fileName = context->compiledNameInput->value();
  context->commandBuilder->addOutputFileOption(fileName);
  context->commandBuilder->buildCommand();
  context->commandBuilder->writeCommandToBuffer(context->buffer);
}

} // namespace

void mainWindow::createWindow() {
  Fl::set_font(FL_HELVETICA, "DejaVu Sans");
  Fl::set_font(FL_HELVETICA_BOLD, "DejaVu Sans");
  Fl::set_font(FL_COURIER, "DejaVu Sans Mono");

  Fl_Tooltip::font(FL_HELVETICA);
  Fl_Tooltip::size(14);

  auto *window = new Fl_Double_Window(612, 230, 770, 677, "Code Analysis");

  auto *term = new linuxTerminal(19, 383, 740, 280);

  auto *tabs = new Fl_Tabs(19, 27, 744, 345);
  {
    auto *group1 = new Fl_Group(25, 63, 738, 309);
    group1->label("clang-tidy");
    group1->labelfont(14);
    group1->tooltip("clang-tidy\n"
                    "Статический анализатор кода от LLVM/Clang.\n"
                    "Проверяет исходный код БЕЗ запуска программы.\n"
                    "Помогает находить:\n"
                    "* ошибки логики\n"
                    "* потенциальные баги\n"
                    "* проблемы современного C++\n"
                    "* нарушения style guide\n"
                    "* рекомендации по modern C++\n"
                    "Использует compile_commands.json\n"
                    "для понимания include и флагов компиляции.\n"
                    "Подходит для улучшения качества кода");

    auto *tree = new tipTree(35, 135, 718, 148);
    tree->begin();
    tree->initTipTree();
    tree->selectmode(FL_TREE_SELECT_MULTI);
    tree->root_label("sections");
    tree->callback(tipTree::treeCb);

    tree->add("bugprone-*/bugprone-assert-side-effect");
    tree->add("bugprone-*/bugprone-copy-constructor-init");
    tree->add("bugprone-*/bugprone-infinite-loop");
    tree->add("bugprone-*/bugprone-use-after-move");
    tree->add("bugprone-*/bugprone-sizeof-expression");
    tree->add("bugprone-*/bugprone-suspicious-missing-comma");
    tree->add("bugprone-*/bugprone-virtual-near-miss");

    tree->add("modernize-*/modernize-use-nullptr");
    tree->add("modernize-*/modernize-use-override");
    tree->add("modernize-*/modernize-loop-convert");
    tree->add("modernize-*/modernize-make-unique");
    tree->add("modernize-*/modernize-make-shared");
    tree->add("modernize-*/modernize-use-auto");
    tree->add("modernize-*/modernize-use-emplace");

    tree->add("readability-*/readability-braces-around-statements");
    tree->add("readability-*/readability-identifier-naming");
    tree->add("readability-*/readability-function-size");
    tree->add("readability-*/readability-magic-numbers");
    tree->add("readability-*/readability-uppercase-literal-suffix");

    tree->add("performance-*/performance-for-range-copy");
    tree->add("performance-*/performance-move-const-arg");
    tree->add("performance-*/performance-unnecessary-copy-initialization");
    tree->add("performance-*/performance-inefficient-string-concatenation");

    tree->add("cppcoreguidelines-*/cppcoreguidelines-owning-memory");
    tree->add("cppcoreguidelines-*/cppcoreguidelines-pro-type-cstyle-cast");
    tree->add("cppcoreguidelines-*/cppcoreguidelines-special-member-functions");
    tree->add("cppcoreguidelines-*/cppcoreguidelines-avoid-goto");

    tree->add("misc-*/misc-definitions-in-headers");
    tree->add("misc-*/misc-unused-parameters");
    tree->add("misc-*/misc-non-private-member-variables-in-classes");
    tree->add("misc-*/misc-throw-by-value-catch-by-reference");
    std::println("Tree created!");

    tree->end();

    auto *mainFileInput = new Fl_File_Input(227, 63, 422, 32, "main.cpp:");
    mainFileInput->tooltip("Укажите путь до main.cpp файла проекта");

    auto *fileInput = new Fl_File_Input(227, 95, 422, 32, "AST file:");
    fileInput->tooltip(
        "Укажите compile_commands.json — инструкцию для clang-tidy,"
        "как собирать проект (include-пути, стандарт C++, define'ы)."
        "Без этого файла анализ будет неполным и неточным.");

    auto *browseMainButton = new Fl_Button(653, 67, 100, 28, "Обзор...");
    browseMainButton->callback(
        [](Fl_Widget *widget, void *data) -> void {
          auto *input = static_cast<Fl_File_Input *>(data);
          char *file = fl_file_chooser("Выберите main.cpp", "*.*", nullptr);
          if (file != nullptr) {
            input->value(file);
          }
        },
        mainFileInput);

    auto *browseAstButton = new Fl_Button(653, 99, 100, 28, "Обзор...");
    browseAstButton->callback(
        [](Fl_Widget *widget, void *data) -> void {
          auto *input = static_cast<Fl_File_Input *>(data);
          char *file = fl_dir_chooser(
              "Выберите папку, содержащую compile_commands.json", nullptr);
          if (file != nullptr) {
            input->value(file);
          }
        },
        fileInput);

    auto *enableAST = new checkBoxAST(43, 99, 116, 22, "enable AST");
    checkBoxAST::addWidgetsToControl(fileInput, browseAstButton);
    enableAST->value(1);
    enableAST->callback(checkBoxAST::controlCb, &checkBoxAST::wtc);
    enableAST->tooltip(
        "AST — промежуточное представление кода в виде дерева.\n"
        "Вкл.: быстрый анализ, но может пропустить макросы/шаблоны.\n"
        "Выкл.: медленнее, зато проверяет реальный код после "
        "препроцессора.");

    auto *boxCommandLabel = new Fl_Box(29, 315, 146, 40, "Команда: ");

    auto *commandDisplay = new Fl_Text_Display(193, 315, 560, 40);
    auto *commandBuffer = new Fl_Text_Buffer();
    commandDisplay->buffer(commandBuffer);

    auto *addButton = new Fl_Button(643, 285, 110, 24, "Добавить");
    auto *addButtonCtx = new commandBuilderCLContext;
    addButtonCtx->astButton = enableAST;
    addButtonCtx->commandBuffer = commandBuffer;
    addButtonCtx->astPath = fileInput;
    addButtonCtx->mainFilePath = mainFileInput;
    addButtonCtx->tree = tree;
    addButtonCtx->astCheck = enableAST;
    addButton->callback(addButtonCb, addButtonCtx);

    auto *clearButton = new Fl_Button(539, 285, 100, 24, "Очистить");
    clearButton->callback(clearButtonCb, commandBuffer);

    auto *enterCommandButton = new Fl_Button(435, 285, 100, 24, "Ввести");
    enterCommandCtx.buffer = commandBuffer;
    enterCommandCtx.term = term;
    enterCommandButton->callback(
        [](Fl_Widget *widget, void *data) -> void {
          auto *context = static_cast<enterCommandContext *>(data);
          context->term->enterCommandToTerminal(context->buffer->text());
        },
        &enterCommandCtx);

    group1->end();
    auto *group2 = new Fl_Group(25, 69, 732, 311);
    {
      group2->label("CppCheck");
      group2->labelfont(14);
      group2->tooltip("cppcheck\n"
                      "Независимый статический анализатор C/C++.\n"
                      "Проверяет исходный код БЕЗ запуска программы.\n"
                      "Помогает находить:\n"
                      "* потенциальные ошибки\n"
                      "* утечки памяти\n"
                      "* suspicious code\n"
                      "* неиспользуемый код\n"
                      "* portability проблемы\n"
                      "Часто проще в настройке,\n"
                      "чем clang-tidy.\n"
                      "Хорошо подходит как дополнительная проверка");

      auto *projectPath = new Fl_File_Input(138, 79, 470, 34);
      projectPath->label("json file:");
      projectPath->tooltip("Укажите путь до директории compile_commands.json");
      auto *browseProjectPathButton = new Fl_Button(627, 79, 103, 34);
      browseProjectPathButton->label("Обзор...");
      browseProjectPathButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *projectPath = static_cast<Fl_File_Input *>(data);
            const char *path = fl_file_chooser(
                "Укажите папку, содержащую compile_commands.json", nullptr,
                "*.*");
            projectPath->value(path);
          },
          projectPath);
      auto *commandLineCppCheck = new Fl_Text_Display(193, 315, 560, 40);
      auto *commandBufferCppCheck = new Fl_Text_Buffer();
      auto *commandLabel = new Fl_Box(29, 315, 146, 40, "Команда: ");
      commandLineCppCheck->buffer(commandBufferCppCheck);

      auto *treeCppCheck = new tipTreeCppCheck(35, 135, 718, 148);
      treeCppCheck->initMap();
      treeCppCheck->root_label("sections");

      treeCppCheck->add("warning");
      treeCppCheck->add("style");
      treeCppCheck->add("performance");
      treeCppCheck->add("portability");
      treeCppCheck->add("information");
      treeCppCheck->add("unusedFunction");
      treeCppCheck->add("missingInclude");
      treeCppCheck->add("all");

      treeCppCheck->callback(tipTreeCppCheck::treeCb, nullptr);

      auto *addButton = new Fl_Button(643, 285, 110, 24, "Добавить");
      addButton->tooltip("Добавить параметры в строку команды");
      auto *commandBuilder = new CommandBuilderCppCheck();
      auto *context =
          new CommandBuilderCppCheckContext{.buffer = commandBufferCppCheck,
                                            .commandBuilder = commandBuilder,
                                            .tipTreeCppCheck = treeCppCheck,
                                            .projectPath = projectPath};
      addButton->callback(addButtonCbCppCheck, context);

      auto *clearButton = new Fl_Button(539, 285, 100, 24, "Очистить");
      clearButton->tooltip("Очистить командную строку");
      clearButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *context = static_cast<CommandBuilderCppCheckContext *>(data);
            context->buffer->text("");
            context->commandBuilder->resetCommand();
          },
          context);

      auto *enterButton = new Fl_Button(435, 285, 100, 24, "Ввести");
      enterButton->tooltip("Ввести команду в терминал");

      auto *enterCommandCppCheckContext = new enterCommandContext{
          .buffer = commandBufferCppCheck, .term = term};
      enterButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *context = static_cast<enterCommandContext *>(data);
            context->term->enterCommandToTerminal(context->buffer->text());
          },
          enterCommandCppCheckContext);
    }
    group2->end();
    auto *group3 = new Fl_Group(25, 69, 738, 303);
    {
      group3->label("AddressSanitizer");
      group3->labelfont(14);
      group3->tooltip("addressSanitizer\n"
                      "Runtime анализатор ошибок памяти.\n"
                      "Работает во время запуска программы,\n"
                      "а не анализа исходного кода.\n"
                      "Помогает обнаружить:\n"
                      "* выход за границы массива\n"
                      "* use-after-free\n"
                      "* double free\n"
                      "* переполнение stack/heap\n"
                      "* утечки памяти\n"
                      "Требует сборки с:\n"
                      "-fsanitize=address\n"
                      "Рекомендуется использовать\n"
                      "в Debug режиме");
      auto *mainFileInput = new Fl_File_Input(227, 63, 422, 32, "main.cpp:");
      mainFileInput->tooltip("Укажите путь до main.cpp файла проекта");
      auto *fileOutputName =
          new Fl_Input(227, 105, 422, 22, "Имя исполняемого файла:");
      fileOutputName->tooltip("Укажите название для скомпилированного файла");

      auto *browseMainButton = new Fl_Button(653, 67, 100, 28, "Обзор...");
      browseMainButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *input = static_cast<Fl_File_Input *>(data);
            char *file = fl_file_chooser("Выберите main.cpp", "*.*", nullptr);
            if (file != nullptr) {
              input->value(file);
            }
          },
          mainFileInput);
      auto *treeASanCheck = new tipTreeASan(35, 135, 718, 148);
      treeASanCheck->initMap();
      treeASanCheck->root_label("sections");
      treeASanCheck->add("address");
      treeASanCheck->add("undefined");
      treeASanCheck->add("leak");
      treeASanCheck->add("thread");
      treeASanCheck->add("memory");
      treeASanCheck->add("hwaddress");
      treeASanCheck->add("pointer-compare");
      treeASanCheck->add("pointer-subtract");
      treeASanCheck->add("bounds");
      treeASanCheck->add("alignment");
      treeASanCheck->add("null");
      treeASanCheck->add("return");
      treeASanCheck->add("vptr");
      treeASanCheck->add("integer");
      treeASanCheck->add("all");
      treeASanCheck->callback(tipTreeCppCheck::treeCb, nullptr);

      auto *commandLine = new Fl_Text_Display(193, 315, 560, 40);
      auto *commandBuffer = new Fl_Text_Buffer();
      auto *commandLabel = new Fl_Box(29, 315, 146, 40, "Команда: ");

      commandLine->buffer(commandBuffer);

      auto *addButton = new Fl_Button(643, 285, 110, 24, "Добавить");
      addButton->tooltip("Добавить параметры в строку команды");
      auto *commandBuilder = new CommandBuilderASan();
      auto *context =
          new CommandBuilderASanContext{.buffer = commandBuffer,
                                        .commandBuilder = commandBuilder,
                                        .tipTreeASanCheck = treeASanCheck,
                                        .compiledNameInput = fileOutputName,
                                        .mainFilePath = mainFileInput};
      addButton->callback(addButtonCbASanCheck, context);

      auto *clearButton = new Fl_Button(539, 285, 100, 24, "Очистить");
      clearButton->tooltip("Очистить командную строку");
      clearButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *context = static_cast<CommandBuilderASanContext *>(data);
            context->buffer->text("");
            context->commandBuilder->resetCommand();
          },
          context);

      auto *enterButton = new Fl_Button(435, 285, 100, 24, "Ввести");
      enterButton->tooltip("Ввести команду в терминал");

      auto *enterCommandCppCheckContext =
          new enterCommandContext{.buffer = commandBuffer, .term = term};
      enterButton->callback(
          [](Fl_Widget *widget, void *data) -> void {
            auto *context = static_cast<enterCommandContext *>(data);
            context->term->enterCommandToTerminal(context->buffer->text());
          },
          enterCommandCppCheckContext);
    }
    group3->end();

    auto *pages = new widgetData::tabsPages(tabs, group1, group2, group3);
  }
  tabs->end();

  auto *groupTerminal = new Fl_Group(19, 383, 740, 280);
  {

    groupTerminal->add(term);
    term->enterFirstPromt();
    term->createPTY();

    // windows terminal
  }
  groupTerminal->end();

  window->end();
  window->show();
}

void mainWindow::changeTabCallback(Fl_Widget *widget, void *data) {
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
