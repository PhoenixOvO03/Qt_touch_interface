#include "functionbutton.h"
#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

FunctionButton::FunctionButton(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);

    // 初始化成员
    m_name = new QLabel("app");
    m_functionBtn = new QPushButton();
    m_functionBtn->setFixedSize(100,100);
    m_functionBtn->setIconSize(QSize(100,100));
    m_functionBtn->setFlat(true);

    // 按钮居中
    QHBoxLayout* hLayout_btn = new QHBoxLayout();
    hLayout_btn->addStretch(1);
    hLayout_btn->addWidget(m_name);
    hLayout_btn->addStretch(1);

    // 名字居中
    QHBoxLayout* hLayout_name = new QHBoxLayout();
    hLayout_name->addStretch(1);
    hLayout_name->addWidget(m_functionBtn);
    hLayout_name->addStretch(1);

    // 整体居中
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout_name);
    vLayout->addLayout(hLayout_btn);
    vLayout->addStretch(1);
}

FunctionButton::FunctionButton(const QString &name, QWidget *parent)
    : FunctionButton(parent)
{
    m_name->setText(name);
    connect(m_functionBtn, &QPushButton::clicked,[&](){
        emit clicked(this);
    });

    if (name == "隐藏")
    {
        m_functionBtn->setIcon(QIcon(":/img/hide.png"));
        m_description = "隐藏所有app";
    }
    else if (name == "关闭")
    {
        m_functionBtn->setIcon(QIcon(":/img/close.png"));
        m_description = "关闭当前窗口";
    }
    else
    {
        m_functionBtn->setIcon(QIcon(":/img/qt.png"));
        m_description = "暂无功能";
    }
}

void FunctionButton::function(MainWindow *window)
{
    if (m_name->text() == "隐藏")
    {
        window->hideApps(true);
    }
    else if (m_name->text() == "关闭")
    {
        window->close();
    }
}

void FunctionButton::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);

    // 鼠标进入按钮放大、显示详情
    m_functionBtn->setFixedSize(140,140);
    m_functionBtn->setIconSize(QSize(140,140));
    emit hover(m_description);
    update();
}

void FunctionButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    // 鼠标离开按钮复原、关闭详情
    m_functionBtn->setFixedSize(100,100);
    m_functionBtn->setIconSize(QSize(100,100));
    emit hover("");
    update();
}
