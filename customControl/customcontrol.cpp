#include "customcontrol.h"

CustomControl::CustomControl(QWidget *parent)
    : Software{parent}
{
    m_switchButton = new MySwitchButton(this);
    m_switchButton->move(10,10);
}
