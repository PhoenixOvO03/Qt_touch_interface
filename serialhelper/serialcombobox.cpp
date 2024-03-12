#include "serialcombobox.h"

#include <QLabel>
#include <QComboBox>

SerialComboBox::SerialComboBox(QWidget *parent)
    : QWidget{parent}
{
    // 界面初始化
    this->setFixedSize(100, 50);
    m_label = new QLabel(this);
    m_comboBox = new QComboBox(this);
    m_comboBox->setFixedSize(100,30);
    m_comboBox->move(0,20);
}

SerialComboBox::SerialComboBox(QString name, QWidget *parent)
    : SerialComboBox(parent)
{
    m_label->setText(name);

    // 根据名字选择初始化参数
    if (name == "波特率") setItems(QStringList() << "4800" << "9600" << "19200");
    else if (name == "数据位") setItems(QStringList() << "8");
    else if (name == "停止位") setItems(QStringList() << "1" << "2");
    else if (name == "校验位") setItems(QStringList() << "无校验" << "奇校验" << "偶校验");
    else if (name == "发送格式") setItems(QStringList() << "HEX" << "文本");
    else if (name == "接收格式") setItems(QStringList() << "HEX" << "文本");
}

QString SerialComboBox::currentText()
{
    return m_comboBox->currentText();
}

void SerialComboBox::setItems(QStringList &items)
{
    m_comboBox->clear();
    m_comboBox->addItems(items);
}
