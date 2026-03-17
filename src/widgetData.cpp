#include "../include/widgetData.hpp"
#include <print>

namespace widgetData {

tabsPages::tabsPages(Fl_Tabs *tabs, Fl_Group *group1, Fl_Group *group2,
                         Fl_Group *group3)
    : m_tabs(tabs), m_group1(group1), m_group2(group2), m_group3(group3) {}

// tab index starts from 1
void tabsPages::setGroup(int index) 
{
    switch (index) {
        case 1:
            m_tabs->value(m_group1);
            break;
        case 2:
            m_tabs->value(m_group2);
            break;
        case 3:
            m_tabs->value(m_group3);
            break;
        default:
            std::println("Error during selecting tabs");
            break;
    
    }
}

int tabsPages::getIndex() const 
{
    return m_tabs->find(m_tabs->value());
}

} // namespace widgetData