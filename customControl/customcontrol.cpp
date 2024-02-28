#include "customcontrol.h"

CustomControl::CustomControl(QWidget *parent)
    : Software{parent}
{
    m_switchButton = new MySwitchButton(this);
    m_switchButton->move(25,25);

    m_sliderHundred = new MySliderHundred(this);
    m_sliderHundred->move(225,25);
}
