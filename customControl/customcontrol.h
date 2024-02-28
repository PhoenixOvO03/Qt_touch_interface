#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include "software.h"
#include "myswitchbutton.h"
#include "mysliderhundred.h"

#include <QWidget>

class CustomControl : public Software
{
    Q_OBJECT
public:
    explicit CustomControl(QWidget *parent = nullptr);

signals:

private:
    MySwitchButton* m_switchButton;     // 开关按钮
    MySliderHundred* m_sliderHundred;   // 滑块
};

#endif // CUSTOMCONTROL_H
