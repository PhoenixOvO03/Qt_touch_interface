#include "app.h"
#include "serialhelper.h"

#include <QIcon>

App::App(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);

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

    connect(m_appBtn, &QAbstractButton::pressed, [&](){emit pressed(m_name->text());});
    connect(m_appBtn, &QPushButton::clicked, [&](){
        if (m_name->text() == "SerialHelper")emit clicked(new SerialHelper(), m_name->text());
    });
}

App::App(const QString &name, QWidget *parent)
    : App(parent)
{
    m_name->setText(name);
    m_appBtn->setIcon(QIcon(QString(":/img/%1.png").arg(name)));
    if (name == "null")m_appBtn->setIcon(QIcon(":/img/qt.png"));
}
