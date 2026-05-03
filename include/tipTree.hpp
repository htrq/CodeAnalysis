#ifndef TIP_TREE_HTRQ_HPP
#define TIP_TREE_HTRQ_HPP
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <unordered_map>
#include <string>

class tipTree : public Fl_Tree {
  Fl_Tree_Item *itemShowingTip{};
  Fl_Tooltip *tooltip{};
  const char *itemLabel{};
  Fl_Tree_Item* last_item = nullptr;
  
  struct Info {
    std::string title;
    std::string description;
  };

  inline static std::unordered_map<std::string, std::string> mapData;




public:
  using Fl_Tree::Fl_Tree;
  static void treeCb(Fl_Widget* widget, void* data);
  void initTipTree();
};

#endif