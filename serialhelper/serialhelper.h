#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include "software.h"
#include "serialcombobox.h"

#include <QPlainTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

class SerialHelper : public Software
{
    Q_OBJECT
public:
    SerialHelper(QWidget* parent = nullptr);

    void interfaceInit();
    void timerInit();
    void connectInit();

protected:

private slots:
    void UartConnect();
    void UartSend();
    void UartDisconnect();

private:
    QPlainTextEdit* m_sendArea;   // 发送区
    QPlainTextEdit* m_recvArea;   // 接收区

    QPushButton* m_clearSendBtn;    // 清空发送区
    QPushButton* m_clearRecvBtn;    // 清空接收区
    QPushButton* m_sendBtn;   // 发送按钮
    QPushButton* m_startBtn;  // 开始按钮
    QPushButton* m_endBtn;    // 结束按钮

    SerialComboBox* m_portNumber;  // 端口号
    SerialComboBox* m_baudRate;    // 波特率
    SerialComboBox* m_dataSize;    // 数据位
    SerialComboBox* m_stopSize;    // 停止位
    SerialComboBox* m_checkSize;   // 校验位
    SerialComboBox* m_sendMode;    // 发送模式
    SerialComboBox* m_recvMode;    // 接收模式

    QSerialPort* m_serialPort;    // 串口
    QStringList m_ports;
    QTimer* m_timer;
};

#endif // SERIALHELPER_H
