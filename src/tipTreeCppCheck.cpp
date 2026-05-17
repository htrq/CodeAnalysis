#include "../include/tipTreeCppCheck.hpp"
#include <FL/Fl_Widget.H>
#include <print>
#include <Fl/Fl_Tooltip.H>
#include <string>
#include <unordered_map>

void tipTreeCppCheck::initMap() {
    optionMap.insert(
        {"warning",
         "Поиск потенциальных ошибок в коде.\n"
         "Проверяет подозрительные конструкции:\n"
         "* обращение к nullptr\n"
         "* выход за границы\n"
         "* ошибки логики\n"
         "* опасные условия\n"
         "Рекомендуется всегда включать"});

    optionMap.insert(
        {"style",
         "Проверка качества и читаемости кода.\n"
         "Помогает найти:\n"
         "* неиспользуемые переменные\n"
         "* лишний код\n"
         "* спорные конструкции\n"
         "* проблемы поддержки\n"
         "Не влияет на работу программы,\n"
         "но помогает поддерживать чистый код"});

    optionMap.insert(
        {"performance",
         "Поиск мест, где код может работать неэффективно.\n"
         "Например:\n"
         "* лишние копирования объектов\n"
         "* неоптимальное использование STL\n"
         "* избыточные временные объекты\n"
         "Полезно для оптимизации"});

    optionMap.insert(
        {"portability",
         "Проверка переносимости кода.\n"
         "Помогает найти код, который может\n"
         "работать по-разному на Linux, Windows\n"
         "или разных архитектурах.\n"
         "Полезно для кроссплатформенной разработки"});

    optionMap.insert(
        {"information",
         "Дополнительные информационные замечания.\n"
         "Показывает рекомендации и подсказки,\n"
         "которые не считаются ошибками.\n"
         "Можно использовать для более\n"
         "подробного анализа проекта"});

    optionMap.insert(
        {"unusedFunction",
         "Поиск неиспользуемых функций.\n"
         "Находит функции, которые объявлены,\n"
         "но нигде не вызываются.\n"
         "Помогает очистить проект\n"
         "от лишнего кода"});

    optionMap.insert(
        {"missingInclude",
         "Проверка проблем с include-файлами.\n"
         "Помогает найти:\n"
         "* отсутствующие заголовки\n"
         "* неверные include пути\n"
         "* проблемы конфигурации проекта\n"
         "Может требовать корректно настроенные пути"});

    optionMap.insert(
        {"all",
         "Включить все проверки сразу.\n"
         "Объединяет:\n"
         "* warning\n"
         "* style\n"
         "* performance\n"
         "* portability\n"
         "* information\n"
         "* unusedFunction\n"
         "* missingInclude\n"
         "Может выдавать много предупреждений"});
}

void tipTreeCppCheck::treeCb(Fl_Widget *widget, void *data) {
  auto *tree = static_cast<class tipTreeCppCheck *>(widget);
  
  if (tree->callback_reason() != FL_TREE_REASON_SELECTED) {
    return;
  }
  
  if (tree->callback_item() != nullptr) {
    auto it = tree->optionMap.find(tree->callback_item()->label());
    if (it != tree->optionMap.end()) {
      std::println("Found description: {}", it->second);
      Fl_Tooltip::enter_area(tree, 0, 0, 1, 1, it->second.c_str());
    }
  }
}