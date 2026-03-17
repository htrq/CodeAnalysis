#ifndef WIDGET_DATA_HPP_HTRQ
#define WIDGET_DATA_HPP_HTRQ

#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>

namespace widgetData {
struct tabsPages {
  tabsPages(Fl_Tabs *tabs, Fl_Group *group1, Fl_Group *group2,
              Fl_Group *group3);

  void setGroup(int index);
  [[nodiscard("index must be used")]] int getIndex() const;

private:
  Fl_Tabs *m_tabs;
  Fl_Group *m_group1;
  Fl_Group *m_group2;
  Fl_Group *m_group3;
};
} // namespace widgetData

#endif