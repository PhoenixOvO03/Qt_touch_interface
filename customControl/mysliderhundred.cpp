#include "mysliderhundred.h"

#include <QPainter>
#include <QMouseEvent>

MySliderHundred::MySliderHundred(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(530,30);

    m_value = 0;
    m_currX = m_value * 5 + height() / 2;
    m_hold = false;

    m_R = height() / 2;
}

void MySliderHundred::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    // 绘制灰色进度条
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(0, 0, width(), height(), m_R, m_R);

    // 绘制左边进度条
    QLinearGradient linear(0, 0, width(), height());
    linear.setColorAt(0.2,QColor(53,179,251,150));//蓝色
    linear.setColorAt(0.8,QColor(255,88,127,200));//红色
    painter.setBrush(linear);
    // painter.setBrush(Qt::blue);
    painter.drawRoundedRect(0, 0, m_currX + m_R, height(), m_R, m_R);

    // 绘制按钮
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(m_currX, m_R), m_R, m_R);
}

void MySliderHundred::mousePressEvent(QMouseEvent *event)
{
    m_value = (event->pos().x() - 15) / 5;
    if (m_value > 100) m_value = 100;
    if (m_value < 0) m_value = 0;
    m_currX = m_value * 5 + height() / 2;
    emit valueChanged(m_value);
    m_hold = true;
    update();
}

void MySliderHundred::mouseMoveEvent(QMouseEvent *event)
{
    if (m_hold)
    {
        m_value = (event->pos().x() - 15) / 5;
        if (m_value > 100) m_value = 100;
        if (m_value < 0) m_value = 0;
        m_currX = m_value * 5 + height() / 2;
        emit valueChanged(m_value);
        update();
    }
}

void MySliderHundred::mousereleaveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_hold = false;
        emit valueChanged(m_value);
    }
}
