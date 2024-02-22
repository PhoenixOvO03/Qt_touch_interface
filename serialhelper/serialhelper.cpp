#include "serialhelper.h"

#include <QLabel>
#include <QMessageBox>
#include <QVector>
#include <QtAlgorithms>

SerialHelper::SerialHelper(Software *parent)
    : Software(parent)
{
    this->setFixedSize(800, 600);

    areaInit();
    setupBtnInit();
    lablesInit();
    statusBtnInit();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [&](){
        QVector<QString> temp;
        for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts())
        {
            temp.push_back(info.portName());
        }
        std::sort(temp.begin(), temp.end());
        if (temp != ports)
        {
            this->m_portNumber->clear();
            this->ports = temp;
            for (auto& a : ports)
            {
                this->m_portNumber->addItem(a);
            }
        }
    });
    m_timer->start(1000);
}

void SerialHelper::areaInit()
{
    // 接收区初始化
    m_recvArea = new QPlainTextEdit(this);
    m_recvArea->setFixedSize(600, 300);
    m_recvArea->move(20, 30);
    m_recvArea->setReadOnly(true);

    // 清空接收区按钮
    m_clearRecvBtn = new QPushButton("清空接收区", this);
    m_clearRecvBtn->setFixedSize(120, 30);
    m_clearRecvBtn->move(500, 350);
    connect(m_clearRecvBtn, &QPushButton::clicked, [&](){m_recvArea->clear();});

    // 发送区初始化
    m_sendArea = new QPlainTextEdit(this);
    m_sendArea->setFixedSize(600, 100);
    m_sendArea->move(20, 410);

    // 发送按钮
    m_sendBtn = new QPushButton("发送", this);
    m_sendBtn->setFixedSize(120, 30);
    m_sendBtn->move(350, 530);
    connect(m_sendBtn, &QPushButton::clicked, [&](){
        QString data = m_sendArea->toPlainText();
        if (m_sendMode->currentText() == "HEX")
        {
            QByteArray arr;
            for (int i = 0; i < data.size(); ++i)
            {
                if (data[i] == ' ')continue;
                int num = data.mid(i, 2).toUInt(nullptr, 16);
                ++i;
                arr.append(num);
            }

            m_serialPort->write(arr);
        }
        else
        {
            m_serialPort->write(data.toLocal8Bit().data());
        }
    });

    // 清空发送去按钮
    m_clearSendBtn = new QPushButton("清空发送区", this);
    m_clearSendBtn->setFixedSize(120, 30);
    m_clearSendBtn->move(500, 530);
    connect(m_clearSendBtn, &QPushButton::clicked, [&](){m_sendArea->clear();});
}

void SerialHelper::setupBtnInit()
{
    // 端口
    m_portNumber = new QComboBox(this);

    // 波特率
    m_baudRate = new QComboBox(this);
    m_baudRate->addItem("4800");
    m_baudRate->addItem("9600");
    m_baudRate->addItem("19200");

    // 数据位
    m_dataSize = new QComboBox(this);
    m_dataSize->addItem("8");

    // 停止位
    m_stopSize = new QComboBox(this);
    m_stopSize->addItem("1");
    m_stopSize->addItem("2");

    // 校验位
    m_checkSize = new QComboBox(this);
    m_checkSize->addItem("无校验");
    m_checkSize->addItem("奇校验");
    m_checkSize->addItem("偶校验");

    // 发送格式
    m_sendMode = new QComboBox(this);
    m_sendMode->addItem("HEX");
    m_sendMode->addItem("文本");

    // 接收格式
    m_recvMode = new QComboBox(this);
    m_recvMode->addItem("HEX");
    m_recvMode->addItem("文本");

    QVector<QComboBox*> setups;
    setups << m_portNumber << m_baudRate << m_dataSize << m_stopSize << m_checkSize << m_sendMode << m_recvMode;

    for (int i = 0; i < setups.size(); ++i)
    {
        setups[i]->setFixedSize(100, 30);
        setups[i]->move(650, 30 + i * 60);
    }
}

void SerialHelper::lablesInit()
{
    QLabel* label1 = new QLabel("接收区", this);
    label1->move(20,10);
    QLabel* label2 = new QLabel("发送区", this);
    label2->move(20,390);

    QLabel* portLable = new QLabel("串口号", this);
    QLabel* baudLable = new QLabel("波特率", this);
    QLabel* dataLable = new QLabel("数据位", this);
    QLabel* stopLable = new QLabel("停止位", this);
    QLabel* checkLable = new QLabel("校验位", this);
    QLabel* sendLable = new QLabel("发送格式", this);
    QLabel* recvLable = new QLabel("接收格式", this);

    QVector<QLabel*> labels;
    labels << portLable << baudLable << dataLable << stopLable << checkLable << sendLable << recvLable;
    for (int i = 0; i < labels.size(); ++i)
    {
        labels[i]->move(660, 10 + i * 60);
    }
}

void SerialHelper::statusBtnInit()
{
    m_startBtn = new QPushButton("连接", this);
    m_startBtn->setFixedSize(100, 30);
    m_startBtn->move(650, 450);

    m_endBtn = new QPushButton("断开连接", this);
    m_endBtn->setFixedSize(100, 30);
    m_endBtn->move(650, 510);

    m_endBtn->setEnabled(false);
    m_sendBtn->setEnabled(false);

    connect(m_startBtn, &QPushButton::clicked, [&](){
        if (m_portNumber->currentText() != "")
        {
            m_startBtn->setEnabled(false);
            m_endBtn->setEnabled(true);
            m_sendBtn->setEnabled(true);
            UartConnect();
        }
        else
        {
            QMessageBox::critical(this, "串口打开失败", "请确认串口是否连接正确");
        }
    });

    connect(m_endBtn, &QPushButton::clicked, [&](){
        m_startBtn->setEnabled(true);
        m_endBtn->setEnabled(false);
        m_sendBtn->setEnabled(false);
        m_serialPort->close();
    });
}

void SerialHelper::UartConnect()
{
    QSerialPort::BaudRate Baud;
    QSerialPort::DataBits Data;
    QSerialPort::StopBits Stop;
    QSerialPort::Parity Check;

    QString port = m_portNumber->currentText();
    QString baud = m_baudRate->currentText();
    QString data = m_dataSize->currentText();
    QString stop = m_stopSize->currentText();
    QString ch = m_checkSize->currentText();

    if (baud == "4800") Baud = QSerialPort::Baud4800;
    else if (baud == "9600") Baud = QSerialPort::Baud9600;
    else if (baud == "19200") Baud = QSerialPort::Baud19200;

    if (data == "8") Data = QSerialPort::Data8;

    if (stop == "1") Stop = QSerialPort::OneStop;
    else if (stop == "2")Stop = QSerialPort::TwoStop;

    if (ch == "无校验") Check = QSerialPort::NoParity;
    if (ch == "奇校验") Check = QSerialPort::OddParity;
    if (ch == "偶校验") Check = QSerialPort::EvenParity;

    m_serialPort = new QSerialPort(this);
    m_serialPort->setBaudRate(Baud);
    m_serialPort->setDataBits(Data);
    m_serialPort->setParity(Check);
    m_serialPort->setStopBits(Stop);
    m_serialPort->setPortName(port);

    if (m_serialPort->open(QSerialPort::ReadWrite))
    {
        connect(m_serialPort, &QSerialPort::readyRead, [&](){
            auto data = m_serialPort->readAll();
            if (m_recvMode->currentText() == "HEX")
            {
                QString hex = data.toHex(' ');
                m_recvArea->appendPlainText(hex);
            }
            else
            {
                QString str = QString(data);
                m_recvArea->appendPlainText(str);
            }
        });
    }
    else
    {
        QMessageBox::critical(this, "串口打开失败", "请确认串口是否连接正确");
    }
}

// void SerialHelper::timeEvent(QTimerEvent *event)
// {
//     QVector<QString> temp;
//     for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts())
//     {
//         temp.push_back(info.portName());
//     }
//     qDebug() << temp.size();
//     std::sort(temp.begin(), temp.end());
//     if (temp != ports)
//     {
//         this->m_portNumber->clear();
//         this->ports = temp;
//         for (auto& a : ports)
//         {
//             this->m_portNumber->addItem(a);
//         }
//     }
// }
