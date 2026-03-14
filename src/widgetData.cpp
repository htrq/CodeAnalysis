#include "../include/widgetData.hpp"

namespace widgetData {

wizardPages::wizardPages(Fl_Wizard *wizard, Fl_Group *group1, Fl_Group *group2,
                         Fl_Group *group3)
    : m_wizard(wizard), m_group1(group1), m_group2(group2), m_group3(group3) {}

} // namespace widgetData