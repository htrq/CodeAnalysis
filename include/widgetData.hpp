#ifndef WIDGET_DATA_HPP_HTRQ
#define WIDGET_DATA_HPP_HTRQ

#include <FL/Fl_Group.H>
#include <FL/Fl_Wizard.H>

namespace widgetData {
struct wizardPages {
  wizardPages(Fl_Wizard *wizard, Fl_Group *group1, Fl_Group *group2,
              Fl_Group *group3);

  void setGroup1()
  {
    m_wizard->value(m_group1);
  }
  void setGroup2()
  {
    m_wizard->value(m_group2);
  }
  void setGroup3()
  {
    m_wizard->value(m_group3);
  }

private:
  Fl_Wizard *m_wizard;
  Fl_Group *m_group1;
  Fl_Group *m_group2;
  Fl_Group *m_group3;
};
} // namespace widgetData

#endif