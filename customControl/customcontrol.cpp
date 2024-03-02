#include "customcontrol.h"

CustomControl::CustomControl(QWidget *parent)
    : Software{parent}
{
    m_switchButton = new MySwitchButton(this);
    m_switchButton->move(25,25);

    m_sliderHundred = new MySliderHundred(this);
    m_sliderHundred->move(225,25);

    m_circleProgress = new MyCircleProgress(this);
    m_circleProgress->move(25, 100);

    connect(m_sliderHundred, &MySliderHundred::valueChanged, m_circleProgress, &MyCircleProgress::setValue);
}
