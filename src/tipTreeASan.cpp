#include "../include/tipTreeASan.hpp"
#include <FL/Fl_Widget.H>
#include <Fl/Fl_Tooltip.H>
#include <print>
#include <string>
#include <unordered_map>

void tipTreeASan::initMap() {
  optionMap.insert({"address", "Поиск ошибок работы с памятью.\n"
                               "Помогает обнаружить:\n"
                               "* выход за границы массива\n"
                               "* use-after-free\n"
                               "* double free\n"
                               "* переполнение stack/heap\n"
                               "* повреждение памяти\n"
                               "Рекомендуется включать почти всегда\n"
                               "при отладке"});

  optionMap.insert({"undefined", "Поиск неопределённого поведения (UB).\n"
                                 "Помогает найти:\n"
                                 "* integer overflow\n"
                                 "* деление на ноль\n"
                                 "* invalid cast\n"
                                 "* некорректные битовые сдвиги\n"
                                 "* нарушение правил языка\n"
                                 "Очень полезно вместе с address"});

  optionMap.insert({"leak", "Поиск утечек памяти.\n"
                            "Показывает объекты,\n"
                            "которые были выделены,\n"
                            "но не освобождены.\n"
                            "Полезно для long-running приложений"});

  optionMap.insert({"thread", "Поиск проблем многопоточности.\n"
                              "Обнаруживает:\n"
                              "* data race\n"
                              "* небезопасный доступ к данным\n"
                              "* проблемы синхронизации\n"
                              "Полезно для std::thread,\n"
                              "mutex и shared data"});

  optionMap.insert({"memory", "Поиск чтения неинициализированной памяти.\n"
                              "Помогает обнаружить:\n"
                              "* использование мусорных значений\n"
                              "* чтение до инициализации\n"
                              "* скрытые ошибки логики\n"
                              "Работает медленнее AddressSanitizer\n"
                              "и обычно требует clang"});

  optionMap.insert({"hwaddress", "Аппаратный AddressSanitizer.\n"
                                 "Похож на address,\n"
                                 "но использует аппаратную поддержку CPU.\n"
                                 "Доступен только\n"
                                 "на некоторых архитектурах"});

  optionMap.insert({"pointer-compare",
                    "Проверка подозрительных сравнений указателей.\n"
                    "Помогает найти:\n"
                    "* сравнение несвязанных указателей\n"
                    "* потенциально ошибочную логику\n"
                    "Обычно используется вместе с address"});

  optionMap.insert({"pointer-subtract",
                    "Проверка некорректной арифметики указателей.\n"
                    "Помогает обнаружить:\n"
                    "* вычитание несвязанных указателей\n"
                    "* ошибки вычисления адресов\n"
                    "Полезно для low-level кода"});

  optionMap.insert({"bounds", "Проверка выхода за границы массива.\n"
                              "Помогает найти:\n"
                              "* индекс вне массива\n"
                              "* ошибки доступа к памяти\n"
                              "Особенно полезно\n"
                              "при работе с массивами"});

  optionMap.insert({"alignment", "Проверка выравнивания памяти.\n"
                                 "Находит ошибки,\n"
                                 "когда объект читается\n"
                                 "по неверно выровненному адресу.\n"
                                 "Полезно для low-level и SIMD кода"});

  optionMap.insert({"null", "Проверка обращения через nullptr.\n"
                            "Помогает обнаружить:\n"
                            "* разыменование nullptr\n"
                            "* опасные обращения к памяти\n"
                            "Полезно для повышения стабильности"});

  optionMap.insert({"return", "Проверка возврата значения.\n"
                              "Находит функции,\n"
                              "которые должны вернуть значение,\n"
                              "но завершаются без return.\n"
                              "Помогает избежать UB"});

  optionMap.insert({"vptr", "Проверка корректности виртуальных объектов.\n"
                            "Помогает найти:\n"
                            "* ошибки polymorphism\n"
                            "* invalid virtual call\n"
                            "* повреждение vtable\n"
                            "Полезно для OOP кода"});

  optionMap.insert({"integer", "Проверка ошибок целочисленных операций.\n"
                               "Помогает обнаружить:\n"
                               "* signed overflow\n"
                               "* опасные арифметические операции\n"
                               "* потерю данных\n"
                               "Полезно для вычислений"});

  optionMap.insert({"all", "Включить основные sanitizer проверки.\n"
                           "Часто используют комбинацию:\n"
                           "* address\n"
                           "* undefined\n"
                           "* leak\n"
                           "Может заметно замедлить программу,\n"
                           "но даёт максимальную диагностику"});
}

void tipTreeASan::treeCb(Fl_Widget *widget, void *data) {
  auto *tree = static_cast<class tipTreeASan *>(widget);

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