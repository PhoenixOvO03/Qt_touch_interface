#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include "software.h"

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
    SerialHelper(Software* parent = nullptr);

    void areaInit();
    void setupBtnInit();
    void lablesInit();
    void statusBtnInit();
    void UartConnect();

protected:
    // void timeEvent(QTimerEvent* event);

private:
    QPlainTextEdit* m_sendArea;   // 发送区
    QPlainTextEdit* m_recvArea;   // 接收区

    QPushButton* m_clearSendBtn;    // 清空发送区
    QPushButton* m_clearRecvBtn;    // 清空接收区
    QPushButton* m_sendBtn;   // 发送按钮
    QPushButton* m_startBtn;  // 开始按钮
    QPushButton* m_endBtn;    // 结束按钮

    QComboBox* m_portNumber;  // 端口号
    QComboBox* m_baudRate;    // 波特率
    QComboBox* m_dataSize;    // 数据位
    QComboBox* m_stopSize;    // 停止位
    QComboBox* m_checkSize;   // 校验位
    QComboBox* m_sendMode;    // 发送模式
    QComboBox* m_recvMode;    // 接收模式

    QSerialPort* m_serialPort;    // 串口
    QVector<QString> ports;
    QTimer* m_timer;
};

#endif // SERIALHELPER_H
