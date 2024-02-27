#include "app.h"
#include "serialhelper.h"
#include "musicplayer.h"
#include "customcontrol.h"
#include "painterx.h"

#include <QIcon>
#include <QPainter>

App::App(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);
    m_isHover = false;

    m_name = new QLabel("app");
    m_appBtn = new QPushButton();
    m_appBtn->setFixedSize(100,100);
    m_appBtn->setIconSize(QSize(100,100));
    m_appBtn->setFlat(true);

    QHBoxLayout* hLayout_btn = new QHBoxLayout();
    hLayout_btn->addStretch(1);
    hLayout_btn->addWidget(m_name);
    hLayout_btn->addStretch(1);

    QHBoxLayout* hLayout_name = new QHBoxLayout();
    hLayout_name->addStretch(1);
    hLayout_name->addWidget(m_appBtn);
    hLayout_name->addStretch(1);

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
        m_description = "QPaintEvent QPainter QBrush";
        connect(m_appBtn, &QPushButton::clicked, [&](){
            emit clicked(new CustomControl(), m_name->text(), m_appBtn->icon());
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
    emit pressed(m_description);
    m_isHover = true;
    update();
}

void App::leaveEvent(QEvent *event)
{
    emit pressed("");
    m_isHover = false;
    update();
}

void App::paintEvent(QPaintEvent *event)
{
    if (m_isHover)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 5));
        painter.drawRect(m_appBtn->pos().x()-1, m_appBtn->pos().y()-1, 102, 102);
    }
}
