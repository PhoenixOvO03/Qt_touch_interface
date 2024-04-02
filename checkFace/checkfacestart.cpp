#include "checkfacestart.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

CheckFaceStart::CheckFaceStart(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(800, 600);

    m_signUp = new QPushButton("注册");
    m_signIn = new QPushButton("登录");

    QHBoxLayout* btnsLayout = new QHBoxLayout(this);
    btnsLayout->addWidget(m_signUp);
    btnsLayout->addSpacing(20);
    btnsLayout->addWidget(m_signIn);

    connect(m_signUp, &QPushButton::clicked, this, &CheckFaceStart::signUp);
    connect(m_signIn, &QPushButton::clicked, this, &CheckFaceStart::signIn);
}
