#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include "software.h"

#include <QWidget>

class CustomControl : public Software
{
    Q_OBJECT
public:
    explicit CustomControl(QWidget *parent = nullptr);

signals:
};

#endif // CUSTOMCONTROL_H
