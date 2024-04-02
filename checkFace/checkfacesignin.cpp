#include "checkfacesignin.h"
#include "videolabel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

CheckFaceSignIn::CheckFaceSignIn(QWidget *parent)
    : QWidget{parent}
{
    interfaceInit();
    connectInit();
}

void CheckFaceSignIn::interfaceInit()
{
    this->setFixedSize(800, 600);

    m_videoLabel = new VideoLabel();

    m_openBtn = new QPushButton("打开摄像头");
    m_closeBtn = new QPushButton("关闭摄像头");
    m_returnBtn = new QPushButton("返回");
    m_closeBtn->setEnabled(false);

    QVBoxLayout* btnsLayout = new QVBoxLayout();
    btnsLayout->addWidget(m_openBtn);
    btnsLayout->addWidget(m_closeBtn);
    btnsLayout->addWidget(m_returnBtn);

    QHBoxLayout* allLayout = new QHBoxLayout(this);
    allLayout->addWidget(m_videoLabel);
    allLayout->addLayout(btnsLayout);
}

void CheckFaceSignIn::connectInit()
{
    connect(m_openBtn, &QPushButton::clicked, this, &CheckFaceSignIn::openCamera);
    connect(m_closeBtn, &QPushButton::clicked, this, &CheckFaceSignIn::closeCamera);
    connect(m_returnBtn, &QPushButton::clicked, this, [&](){
        closeCamera();
        emit returnBack();
    });
}

void CheckFaceSignIn::openCamera() //打开摄像头
{
    m_videoLabel->openCamera();
    m_openBtn->setEnabled(false);
    m_closeBtn->setEnabled(true);
}

void CheckFaceSignIn::closeCamera()//关闭摄像头
{
    m_videoLabel->closeCamera();
    m_openBtn->setEnabled(true);
    m_closeBtn->setEnabled(false);
}

