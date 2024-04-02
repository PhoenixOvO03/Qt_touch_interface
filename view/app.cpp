#include "app.h"
#include "serialhelper.h"
#include "musicplayer.h"
#include "customcontrol.h"
#include "painterx.h"
#include "checkface.h"

#include <QIcon>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

App::App(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);

    // 初始化成员
    m_name = new QLabel("app");
    m_appBtn = new QPushButton();
    m_appBtn->setFixedSize(100,100);
    m_appBtn->setIconSize(QSize(100,100));
    m_appBtn->setFlat(true);

    // 按钮居中
    QHBoxLayout* hLayout_btn = new QHBoxLayout();
    hLayout_btn->addStretch(1);
    hLayout_btn->addWidget(m_name);
    hLayout_btn->addStretch(1);

    // 名字居中
    QHBoxLayout* hLayout_name = new QHBoxLayout();
    hLayout_name->addStretch(1);
    hLayout_name->addWidget(m_appBtn);
    hLayout_name->addStretch(1);

    // 整体居中
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout_name);
    vLayout->addLayout(hLayout_btn);
    vLayout->addStretch(1);
}

App::App(const QString &name, QWidget *parent)
    : App(parent)
{
    m_name->setText(name);

    // 根据名字设置app相关消息
    // 根据名字设置对应software
    if (name == "串口助手")
    {
        m_appBtn->setIcon(QIcon(":/img/SerialHelper.png"));
        m_description = "QSerial QComboBox QTimer";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new SerialHelper(), m_name->text(), m_appBtn->icon());
        });
    }
    else if (name == "音乐播放器")
    {
        m_appBtn->setIcon(QIcon(":/img/musicPlayer.png"));
        m_description = "QMediaPlayer QAudioOutput QSlider";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new musicPlayer(), m_name->text(), m_appBtn->icon());
        });
    }
    else if (name == "绘图效果预览")
    {
        m_appBtn->setIcon(QIcon(":/img/PainterX.png"));
        m_description = "QPaintEvent QPainter QBrush";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new PainterX(), m_name->text(), m_appBtn->icon());
        });
    }
    else if (name == "自定义控件")
    {
        m_appBtn->setIcon(QIcon(":/img/CustomControl.png"));
        m_description = "QPaintEvent QPainter QBrush QPropertyAnimation";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new CustomControl(), m_name->text(), m_appBtn->icon());
        });
    }
    else if (name == "人脸识别")
    {
        m_appBtn->setIcon(QIcon(":/img/checkFace.png"));
        m_description = "OpenCV";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new CheckFace(), m_name->text(), m_appBtn->icon());
        });
    }
    else
    {
        m_appBtn->setIcon(QIcon(":/img/qt.png"));
        m_description = "暂无app";
    }
}

void App::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);

    // 鼠标进入按钮放大、显示详情
    m_appBtn->setFixedSize(140,140);
    m_appBtn->setIconSize(QSize(140,140));
    emit hover(m_description);
    update();
}

void App::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    // 鼠标离开按钮复原、关闭详情
    m_appBtn->setFixedSize(100,100);
    m_appBtn->setIconSize(QSize(100,100));
    emit hover("");
    update();
}
