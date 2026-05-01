#include "../include/tipTree.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <FL/Fl_Group.H>
#include <print>

void tipTree::treeCb(Fl_Widget *widget, void *data) {
  auto *tree = static_cast<class tipTree *>(widget);
  tree->itemShowingTip = tree->callback_item();
  if (tree->itemShowingTip != nullptr) {
    tree->posX = tree->itemShowingTip->x();
    tree->posY = tree->itemShowingTip->y();
    tree->itemLabel = tree->itemShowingTip->label();
    std::println("Returned item label: {}", tree->itemLabel);
    auto it = tipTree::mapData.find(tree->itemLabel);
    if (it != tipTree::mapData.end()) {
      std::println("Found description: {}", it->second.description);
      Fl_Tooltip::enter_area(tree, Fl::event_x(), Fl::event_y(), 1, 1,
                             it->second.description.c_str());
    }
  }
}

void tipTree::initTipTree() {
  tipTree::mapData.insert(
      {"assert-side-effect",
       Info{.title = "assert-side-effect",
            .description = "Ищет побочные эффекты внутри assert(...). В "
                           "release-сборке assert отключается, и важный код "
                           "внутри него может не выполниться."}});
  Fl_Tooltip::enable(1);
  Fl_Tooltip::size(14);
  Fl_Tooltip::font(FL_FREE_FONT);
}
