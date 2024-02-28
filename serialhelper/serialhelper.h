#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include "software.h"

#include <QPlainTextEdit>
#include <QPushButton>
#include <QSerialPort>

class SerialComboBox;

class SerialHelper : public Software
{
    Q_OBJECT
public:
    SerialHelper(QWidget* parent = nullptr);

    void interfaceInit();   // 界面初始化
    void timerInit();       // 定时器初始化
    void connectInit();     // connect函数初始化

protected:

private slots:
    void UartConnect();     // Uart连接
    void UartSend();        // Uart传输数据
    void UartDisconnect();  // Uart断开连接

private:
    QPlainTextEdit* m_sendArea;   // 发送区
    QPlainTextEdit* m_recvArea;   // 接收区

    QPushButton* m_clearSendBtn;    // 清空发送区
    QPushButton* m_clearRecvBtn;    // 清空接收区
    QPushButton* m_sendBtn;   // 发送按钮
    QPushButton* m_startBtn;  // 开始按钮
    QPushButton* m_endBtn;    // 结束按钮

    SerialComboBox* m_portNumber;   // 端口号
    SerialComboBox* m_baudRate;     // 波特率
    SerialComboBox* m_dataSize;     // 数据位
    SerialComboBox* m_stopSize;     // 停止位
    SerialComboBox* m_checkSize;    // 校验位
    SerialComboBox* m_sendMode;     // 发送模式
    SerialComboBox* m_recvMode;     // 接收模式

    QSerialPort* m_serialPort;      // 串口
    QStringList m_ports;            // 端口
    QTimer* m_timer;                // 定时器
};

#endif // SERIALHELPER_H
