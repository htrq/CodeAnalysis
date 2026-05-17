#ifndef TIP_TREE_CPP_CHECK_HPP_HTRQ
#define TIP_TREE_CPP_CHECK_HPP_HTRQ

#include <string>
#include <unordered_map>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Widget.H>

class tipTreeCppCheck : public Fl_Tree {
    std::unordered_map<std::string, std::string> optionMap;
public:
    using Fl_Tree::Fl_Tree; 
    static void treeCb(Fl_Widget* widget, void* data);
    void initMap();
};

#endif