#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    m_firstFloor = new QHBoxLayout();
    m_firstFloor->addStretch(1);
    m_firstFloor->addWidget(new App("我"));
    m_firstFloor->addWidget(new App("爱"));
    m_firstFloor->addWidget(new App("茶"));
    m_firstFloor->addWidget(new App("茶"));
    m_firstFloor->addStretch(1);

    m_secondFloor = new QHBoxLayout();
    m_secondFloor->addStretch(1);
    m_secondFloor->addWidget(new App("null"));
    m_secondFloor->addWidget(new App("null"));
    m_secondFloor->addWidget(new App("null"));
    m_secondFloor->addWidget(new App("null"));
    m_secondFloor->addStretch(1);

    m_thirdFllor = new QHBoxLayout();
    m_thirdFllor->addStretch(1);
    m_thirdFllor->addWidget(new App("null"));
    m_thirdFllor->addWidget(new App("null"));
    m_thirdFllor->addWidget(new App("null"));
    m_thirdFllor->addWidget(new App("close",":/img/close.png"));
    m_thirdFllor->addStretch(1);

    m_allApp = new QVBoxLayout();
    m_allApp->addStretch(1);
    m_allApp->addLayout(m_firstFloor);
    m_allApp->addLayout(m_secondFloor);
    m_allApp->addLayout(m_thirdFllor);
    m_allApp->addStretch(1);

    ui->centralwidget->setLayout(m_allApp);
}

MainWindow::~MainWindow()
{
    delete ui;
}
