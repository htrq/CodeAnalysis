#include "../include/tipTree.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <print>

void tipTree::treeCb(Fl_Widget *widget, void *data) {
  auto *tree = static_cast<class tipTree *>(widget);
  if (tree->callback_reason() != FL_TREE_REASON_SELECTED) {
    return;
  }
  tree->itemShowingTip = tree->callback_item();
  if (tree->itemShowingTip != nullptr) {
    tree->itemLabel = tree->itemShowingTip->label();
    std::println("Returned item label: {}", tree->itemLabel);
    auto it = tipTree::mapData.find(tree->itemLabel);
    if (it != tipTree::mapData.end()) {
      std::println("Found description: {}", it->second);
      Fl_Tooltip::enter_area(tree, 0, 0, 1, 1, it->second.c_str());
    }
  }
}

void tipTree::initTipTree() {
  tipTree::mapData.insert(
      {"bugprone",
       "«Подозрительный код / Скорее всего баг»\n"
       "Чеки, которые ищут паттерны, похожие на опечатки или логические ошибки."
       "Код компилируется и часто даже работает, но делает не то, что задумал "
       "программист."
       "Это не стиль или производительность — это потенциальные баги, которые "
       "сложно отловить глазами."});
  tipTree::mapData.insert(
      {"assert-side-effect",
       "Ищет побочные эффекты внутри assert(...).\n"
       "В release-сборке assert отключается (#define assert(x) ((void)0)), "
       "и важный код внутри него не выполнится. Например: assert(ptr = "
       "malloc(100)) — утечка в release."});
  tipTree::mapData.insert(
      {"copy-constructor-init",
       "Copy-конструктор, который не инициализирует все поля\n"
       "Если добавили поле в класс, но забыли в copy-конструкторе — "
       "новый объект получит мусор/дефолтные значения."});
  tipTree::mapData.insert(
      {"infinite-loop",
       "Циклы while, for, do-while, которые никогда не завершатся\n"
       "Бесконечный цикл = зависание программы."
       "Часто из-за того, что переменная цикла не меняется внутри тела."});
  tipTree::mapData.insert({"use-after-move",
                           "Использование объекта после std::move()\n"
                           "После std::move(x) объект x в \"опустошённом\" "
                           "состоянии (moved from state)."
                           "Его чтение — UB или логические ошибки."});
  tipTree::mapData.insert(
      {"sizeof-expression",
       "Подозрительное использование sizeof\n"
       "Например: sizeof(ptr) вместо sizeof(*ptr), sizeof(expr) < 0, sizeof(42)"
       " — часто опечатки, приводящие к неправильной работе с памятью."});
  tipTree::mapData.insert({"suspicious-missing-comma",
                           "Пропущенная запятая в списке инициализации\n"
                           "int a[] = {1, 2 3, 4}; — компилятор склеит 2 3 в "
                           "23, баг будет незаметен."});
  tipTree::mapData.insert(
      {"virtual-near-miss",
       "Функция \"похожа\" на виртуальную, но не переопределяет её\n"
       "Например: virtual void foo(int) в базовом, а в derived void foo(long)"
       "— сигнатуры различаются, override не произошёл, полиморфизм сломан."});
  tipTree::mapData.insert(
      {"modernize", "«Устаревший стиль / Можно написать современнее»\n"
                    "Чеки, которые предлагают заменить старый C++ на "
                    "современный аналог (C++11/14/17/20/23)."
                    "Код работает корректно, но написан «по-старому». "
                    "Исправление делает код короче, безопаснее и читаемее."});
  tipTree::mapData.insert({"use-nullptr",
                           "NULL или 0 → nullptr\n"
                           "nullptr — типизирован, не конфликтует с int, "
                           "безопаснее в перегрузках."});
  tipTree::mapData.insert({"use-override",
                           "Добавить override к виртуальным функциям\n"
                           "Компилятор проверит, что функция реально override. "
                           "Ошибка — если сигнатура не совпадает."});
  tipTree::mapData.insert(
      {"loop-convert", "Ручной цикл по индексам (for (i=0; i<n; i++))\n"
                       "Лишняя переменная-индекс, риск off-by-one ошибки, "
                       "менее читаемо. Range-based for короче и безопаснее."});
  tipTree::mapData.insert(
      {"make-unique",
       "new внутри std::unique_ptr<T>(...)\n"
       "Ручной new не исключение-безопасен: если между new и захватом в "
       "unique_ptr"
       "бросится исключение — утечка. make_unique делает всё атомарно."});
  tipTree::mapData.insert(
      {"make-shared", "new внутри std::shared_ptr<T>(...)\n"
                      "Две отдельные аллокации (объект + control block) вместо "
                      "одной. Не исключение-безопасен. "
                      "make_shared аллоцирует за раз, быстрее и безопаснее."});
  tipTree::mapData.insert(
      {"use-auto", "Явное указание типа, который очевиден из контекста\n"
                   "Длинные типы (std::vector<int>::iterator) шумят в коде. "
                   "При смене типа контейнера придётся править вручную."
                   "auto короче и адаптивен."});
  tipTree::mapData.insert(
      {"use-emplace",
       "push_back/insert с временным объектом\n"
       "Создаётся временный объект, потом копируется/перемещается в контейнер. "
       "emplace конструирует объект прямо в памяти контейнера — без лишних "
       "копий."});
  tipTree::mapData.insert({"readability",
                           "«Читаемость кода»\n"
                           "Чеки, которые ищут код, трудный для чтения и "
                           "понимания. Код работает корректно"
                           ", но написан так, что коллега (или ты сам через "
                           "месяц) потратит лишнее время, чтобы разобраться."
                           " Часто связано с неявными правилами, магическими "
                           "значениями или нарушением конвенций."});
  tipTree::mapData.insert(
      {"braces-around-statements",
       "if/else/for/while без фигурных скобок {}\n"
       "if (cond) doSomething(); — при добавлении второй строки без скобок она "
       "выполнится всегда."
       "Классическая опечатка, сложная для обнаружения глазами."});
  tipTree::mapData.insert(
      {"identifier-naming",
       "Имена переменных/функций/классов не соответствуют конвенции\n"
       "конвенции	int myVariable вместо int my_variable (или наоборот)."
       " Нарушает единообразие проекта, усложняет code review."});

  tipTree::mapData.insert({"function-size",
                           "Слишком большие функции\n"
                           "Функция на 200+ строк делает много всего — сложно "
                           "понять, тестировать и поддерживать. "
                           "Нарушает SRP (Single Responsibility Principle)."});

  tipTree::mapData.insert(
      {"magic-numbers",
       "«Магические» числа в коде\n"
       "if (x > 42) — что такое 42? Константа с именем (MaxBufferSize) "
       "объясняет намерение и централизует изменение."});

  tipTree::mapData.insert({"uppercase-literal-suffix",
                           "Суффиксы литералов в нижнем регистре\n"
                           "42u, 3.14f — u и f похожи на имена переменных. "
                           "42U, 3.14F читаются явнее как часть литерала."});
  tipTree::mapData.insert(
      {"performance",
       "«Производительность»\n"
       "Чеки, которые ищут неоптимальные паттерны — лишние копирования, лишние "
       "аллокации, пропущенные move. "
       "Код работает правильно, но медленнее, чем мог бы. "
       "Особенно важно в горячих циклах и критических секциях."});

  tipTree::mapData.insert(
      {"for-range-copy", "Range-based for с копированием\n"
                         "for (auto x : container) — копирует каждый элемент. "
                         "Для больших объектов — лишний расход CPU и памяти. "
                         "auto& или const auto& решает."});

  tipTree::mapData.insert(
      {"move-const-arg",
       "std::move применён к const объекту\n"
       "std::move(const_obj) — на самом деле копирует, потому что const нельзя "
       "переместить. "
       "Программист думал, что оптимизировал, а получил копирование."});

  tipTree::mapData.insert({"unnecessary-copy-initialization",
                           "Лишнее копирование при инициализации\n"
                           "auto x = func_returning_vector(); — компилятор "
                           "может сделать копию вместо move. "
                           "Или явное копирование, где достаточно ссылки."});

  tipTree::mapData.insert({"inefficient-string-concatenation",
                           "Конкатенация строк в цикле через +\n"
                           "std::string s; for (...) s += a + b; — каждый + "
                           "создаёт временную строку. "
                           "Накопительная конкатенация через += или "
                           "std::ostringstream эффективнее."});

  tipTree::mapData.insert(
      {"cppcoreguidelines",
       "«Ядро C++ / Фундаментальные правила»\n"
       "Чеки на основе C++ Core Guidelines — официальных рекомендаций от "
       "создателей языка. "
       "Ловят нарушения фундаментальных принципов: владение памятью, "
       "типобезопасность, структура классов. "
       "Часто пересекаются с bugprone и modernize, но на более высоком уровне "
       "— архитектура и дизайн."});

  tipTree::mapData.insert(
      {"owning-memory",
       "Сырые указатели как владельцы памяти\n"
       "int* p = new int[100]; — кто удалит? Утечка при исключении, "
       "double-delete при копировании. "
       "std::unique_ptr/std::vector управляют жизнью автоматически."});

  tipTree::mapData.insert(
      {"pro-type-cstyle-cast",
       "C-style cast: (int*)ptr\n"
       "(int*)ptr может делать static_cast, reinterpret_cast или const_cast — "
       "неясно какой. "
       "C++-castы явны и проверяются компилятором строже."});

  tipTree::mapData.insert(
      {"special-member-functions",
       "Класс с кастомным деструктором/копированием, но без остальных\n"
       "Если определил деструктор — скорее всего, управляешь ресурсом. "
       "Забыл copy-ctor или move — правило пяти/трёх нарушено, ресурсы утекут "
       "или скопируются некорректно."});

  tipTree::mapData.insert(
      {"avoid-goto",
       "Использование goto\n"
       "goto ломает структуру кода, делает поток управления непонятным "
       "(spaghetti code). "
       "Современный C++ предлагает RAII, циклы, исключения для всех случаев."});

  tipTree::mapData.insert(
      {"misc", "«Разное / Общие проверки»\n"
               "Чеки, которые не вписываются в другие категории. Ловят общие "
               "проблемы проектирования: "
               "загрязнение заголовков, мёртвый код, нарушение инкапсуляции. "
               "Часто связаны с OOP-принципами и структурой проекта."});

  tipTree::mapData.insert(
      {"definitions-in-headers",
       "Определения функций/переменных в .h файлах\n"
       "Функция в заголовке без inline → ODR violation (One Definition Rule), "
       "линковочные ошибки при включении в несколько .cpp."});

  tipTree::mapData.insert({"unused-parameters",
                           "Параметры функции, которые не используются\n"
                           "Мёртвый код, путает при чтении. Либо баг (забыл "
                           "использовать), либо артефакт рефакторинга. "
                           "Можно убрать или пометить [[maybe_unused]]."});

  tipTree::mapData.insert(
      {"non-private-member-variables-in-classes",
       "Публичные или protected поля в классах\n"
       "Нарушает инкапсуляцию. Внешний код может неконтролируемо менять "
       "состояние. "
       "Для POD-структур (struct) — нормально, для классов — антипаттерн."});

  tipTree::mapData.insert(
      {"throw-by-value-catch-by-reference",
       "throw объекта по значению, но catch по указателю/значению\n"
       "catch (Exception e) — лишнее копирование, slicing при иерархии "
       "исключений. "
       "catch (const Exception& e) — стандартная идиома, без копий и "
       "slicing."});
}
