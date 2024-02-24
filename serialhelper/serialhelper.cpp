#include "serialhelper.h"

#include <QLabel>
#include <QMessageBox>
#include <QVector>
#include <QtAlgorithms>
#include <QVBoxLayout>
#include <QHBoxLayout>

SerialHelper::SerialHelper(QWidget *parent)
    : Software{parent}
{
    interfaceInit();
    connectInit();
    timerInit();
}

void SerialHelper::interfaceInit()
{
    this->setFixedSize(800, 600);

    // 接收区初始化
    m_recvArea = new QPlainTextEdit();
    m_recvArea->setFixedSize(600, 300);
    m_recvArea->setReadOnly(true);

    // 清空接收区按钮
    m_clearRecvBtn = new QPushButton("清空接收区");
    m_clearRecvBtn->setFixedSize(120, 30);
    m_clearRecvBtn->move(500, 350);

    QHBoxLayout* clearRecvBtn = new QHBoxLayout();
    clearRecvBtn->addStretch(1);
    clearRecvBtn->addWidget(m_clearRecvBtn);

    // 发送区初始化
    m_sendArea = new QPlainTextEdit();
    m_sendArea->setFixedSize(600, 100);

    // 发送按钮
    m_sendBtn = new QPushButton("发送");
    m_sendBtn->setFixedSize(120, 30);

    // 清空发送去按钮
    m_clearSendBtn = new QPushButton("清空发送区");
    m_clearSendBtn->setFixedSize(120, 30);

    QHBoxLayout* clearSendBtns = new QHBoxLayout();
    clearSendBtns->addStretch(1);
    clearSendBtns->addWidget(m_sendBtn);
    clearSendBtns->addSpacing(20);
    clearSendBtns->addWidget(m_clearSendBtn);

    QVBoxLayout* leftBoxLayout = new QVBoxLayout();
    leftBoxLayout->addWidget(m_recvArea);
    leftBoxLayout->addLayout(clearRecvBtn);
    leftBoxLayout->addWidget(m_sendArea);
    leftBoxLayout->addLayout(clearSendBtns);

    m_portNumber = new SerialComboBox("串口号");
    m_dataSize = new SerialComboBox("数据位");
    m_baudRate = new SerialComboBox("波特率");
    m_stopSize = new SerialComboBox("停止位");
    m_checkSize = new SerialComboBox("校验位");
    m_sendMode = new SerialComboBox("发送格式");
    m_recvMode = new SerialComboBox("接收格式");

    QVBoxLayout* rightBoxLaout = new QVBoxLayout();
    rightBoxLaout->addWidget(m_portNumber);
    rightBoxLaout->addWidget(m_dataSize);
    rightBoxLaout->addWidget(m_baudRate);
    rightBoxLaout->addWidget(m_stopSize);
    rightBoxLaout->addWidget(m_checkSize);
    rightBoxLaout->addWidget(m_sendMode);
    rightBoxLaout->addWidget(m_recvMode);

    m_startBtn = new QPushButton("连接");
    m_startBtn->setFixedSize(100, 30);

    m_endBtn = new QPushButton("断开连接");
    m_endBtn->setFixedSize(100, 30);

    rightBoxLaout->addWidget(m_startBtn);
    rightBoxLaout->addWidget(m_endBtn);

    QHBoxLayout* allWidget = new QHBoxLayout(this);
    allWidget->addStretch(1);
    allWidget->addLayout(leftBoxLayout);
    allWidget->addStretch(1);
    allWidget->addLayout(rightBoxLaout);
    allWidget->addStretch(1);

    m_endBtn->setEnabled(false);
    m_sendBtn->setEnabled(false);
}

void SerialHelper::timerInit()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [&](){
        QStringList temp;
        for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts())
        {
            temp.push_back(info.portName());
        }
        std::sort(temp.begin(), temp.end());
        if (temp != m_ports)
        {
            m_ports = temp;
            m_portNumber->setItems(m_ports);
        }
    });
    m_timer->start(1000);
}

void SerialHelper::connectInit()
{
    // 清空按钮
    connect(m_clearRecvBtn, &QPushButton::clicked, [&](){m_recvArea->clear();});
    connect(m_clearSendBtn, &QPushButton::clicked, [&](){m_sendArea->clear();});

    // 发送按钮
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

    // 连接按钮
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

    // 断开连接按钮
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
    else if (ch == "奇校验") Check = QSerialPort::OddParity;
    else if (ch == "偶校验") Check = QSerialPort::EvenParity;

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
