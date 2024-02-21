#include "software.h"

#include <QLabel>>

Software::Software(QWidget *parent)
    : QWidget{parent}
{
    this->hide();
    this->setFixedSize(800,600);
    // new QLabel("this is a app", this);
}
