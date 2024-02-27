#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include "software.h"
#include "myswitchbutton.h"

#include <QWidget>

class CustomControl : public Software
{
    Q_OBJECT
public:
    explicit CustomControl(QWidget *parent = nullptr);

signals:

private:
    MySwitchButton* m_switchButton;
};

#endif // CUSTOMCONTROL_H
