#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "app.h"
#include "software.h"
#include "functionbutton.h"

#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_mousePress = false;

    appBottonInit();
    functionButtonInit();
    interfaceInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appBottonInit()
{
    // 按钮数组初始化
    m_appList << new App("串口助手") << new App("音乐播放器") << new App("绘图效果预览") << new App("自定义控件")
              << new App("人脸识别") << new App("null") << new App("null") << new App("null");

    // 初始化press和click点击的connect
    for (int i = 0; i < 8; ++i)
    {
        // 悬停
        connect(m_appList.at(i), &App::hover, [&](QString arg){
            ui->statusbar->showMessage(arg);
        });
        // 点击
        connect(m_appList.at(i), &App::clicked, [&](Software* app, QString name, QIcon icon){
            this->setWindowIcon(icon);
            this->setWindowTitle(name);
            ui->centralwidget->hide();
            m_currentApp = app;
            m_currentApp->setParent(this);
            m_currentApp->show();
        });
    }
}

void MainWindow::functionButtonInit()
{
    // 功能按钮初始化
    m_functionBtnList << new FunctionButton("null") << new FunctionButton("null")
                      << new FunctionButton("null") << new FunctionButton("关闭");

    // 初始化press和click点击的connect
    for (int i = 0; i < 4; ++i)
    {
        // 悬浮
        connect(m_functionBtnList.at(i), &FunctionButton::hover, [&](QString arg){
            ui->statusbar->showMessage(arg);
        });
        // 点击
        connect(m_functionBtnList.at(i), &FunctionButton::clicked, [&](FunctionButton* btn){
            btn->function(this);
        });
    }
}

void MainWindow::interfaceInit()
{
    /*设置去掉窗口边框*/
    this->setWindowFlags(Qt::FramelessWindowHint);

    //主界面
    this->setFixedSize(800,600);
    this->setWindowTitle("Touch_interface");
    this->setWindowIcon(QIcon(":/img/qt.png"));

    // 每一层App
    m_firstFloor = new QHBoxLayout();
    m_firstFloor->addStretch(1);
    for (int i = 0;i < 4; ++i)m_firstFloor->addWidget(m_appList.at(i));
    m_firstFloor->addStretch(1);

    // 第二层App
    m_secondFloor = new QHBoxLayout();
    m_secondFloor->addStretch(1);
    for (int i = 4;i < 8; ++i)m_secondFloor->addWidget(m_appList.at(i));
    m_secondFloor->addStretch(1);

    // 第三层App
    m_thirdFllor = new QHBoxLayout();
    m_thirdFllor->addStretch(1);
    for (int i = 0;i < 4; ++i)m_thirdFllor->addWidget(m_functionBtnList.at(i));
    m_thirdFllor->addStretch(1);

    // 把所有层集合起来
    m_allApp = new QVBoxLayout();
    m_allApp->addStretch(1);
    m_allApp->addLayout(m_firstFloor);
    m_allApp->addLayout(m_secondFloor);
    m_allApp->addLayout(m_thirdFllor);
    m_allApp->addStretch(1);

    // 放到主界面
    ui->centralwidget->setLayout(m_allApp);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 按下Esc退出app显示主界面
    if (event->key() == Qt::Key_Escape && m_currentApp)
    {
        delete m_currentApp;
        m_currentApp = nullptr;
        ui->centralwidget->show();
        this->setWindowTitle("Touch_interface");
        this->setWindowIcon(QIcon(":/img/qt.png"));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_mousePress = true;
    }
    // 点击位置
    m_pressPos = event->globalPos() - pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_mousePress = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePress)
    {
        // 移动位置
        QPoint movePos = event->globalPos();
        move(movePos - m_pressPos);
    }
}
