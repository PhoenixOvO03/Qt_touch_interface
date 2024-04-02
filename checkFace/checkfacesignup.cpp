#include "checkfacesignup.h"
#include "videolabel.h"

#include <QLabel>
#include <QBrush>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

CheckFaceSignUp::CheckFaceSignUp(QWidget *parent)
    : QWidget{parent}
{
    interfaceInit();
    connectInit();
}

void CheckFaceSignUp::interfaceInit()
{
    this->setFixedSize(800, 600);

    QLabel* nemeLabel = new QLabel("名字：");
    m_nameEdit = new QLineEdit();
    m_signUpBtn = new QPushButton("注册");
    m_openBtn = new QPushButton("打开摄像头");
    m_closeBtn = new QPushButton("关闭摄像头");
    m_returnBtn = new QPushButton("返回");

    m_signUpBtn->setEnabled(false);
    m_closeBtn->setEnabled(false);

    QVBoxLayout* btnsLayout = new QVBoxLayout();
    btnsLayout->addStretch(1);
    btnsLayout->addWidget(nemeLabel);
    btnsLayout->addWidget(m_nameEdit);
    btnsLayout->addStretch(1);
    btnsLayout->addWidget(m_signUpBtn);
    btnsLayout->addStretch(1);
    btnsLayout->addWidget(m_openBtn);
    btnsLayout->addStretch(1);
    btnsLayout->addWidget(m_closeBtn);
    btnsLayout->addStretch(1);
    btnsLayout->addWidget(m_returnBtn);
    btnsLayout->addStretch(1);

    m_videoLabel = new VideoLabel();

    QHBoxLayout* allLayout = new QHBoxLayout(this);
    allLayout->addWidget(m_videoLabel);
    allLayout->addLayout(btnsLayout);
}

void CheckFaceSignUp::connectInit()
{
    connect(m_openBtn, &QPushButton::clicked, this, &CheckFaceSignUp::openCamera);
    connect(m_closeBtn, &QPushButton::clicked, this, &CheckFaceSignUp::closeCamera);
    connect(m_returnBtn, &QPushButton::clicked, this, [&](){
        closeCamera();
        emit returnBack();
    });
}

void CheckFaceSignUp::openCamera() //打开摄像头
{
    m_videoLabel->openCamera();
    m_signUpBtn->setEnabled(true);
    m_openBtn->setEnabled(false);
    m_closeBtn->setEnabled(true);
}

void CheckFaceSignUp::closeCamera()//关闭摄像头
{
    m_videoLabel->closeCamera();
    m_signUpBtn->setEnabled(false);
    m_openBtn->setEnabled(true);
    m_closeBtn->setEnabled(false);
}
