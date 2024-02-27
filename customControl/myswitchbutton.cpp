#include "myswitchbutton.h"

#include <QPainter>
#include <QMouseEvent>

MySwitchButton::MySwitchButton(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(150, 50);

    m_isOff = true;
    m_currX = height() / 2;
    m_R = height() / 2;

    m_offBackgroundBrush = Qt::gray;
    m_onBackgroundBrush = Qt::blue;

    m_indicatorBrush = Qt::white;

    m_offText = "OFF";
    m_onText = "ON";

    update();

    m_animation = new QPropertyAnimation(this);
    m_animation->setTargetObject(this);
    m_animation->setEasingCurve(QEasingCurve::OutBounce);
    m_animation->setDirection(QVariantAnimation::Forward);
    m_animation->setDuration(500);

    connect(m_animation, &QPropertyAnimation::valueChanged, [&](const QVariant& value){
        m_currX = value.toInt();
        update();
    });
}

void MySwitchButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    // 绘制左边进度条
    painter.setBrush(m_onBackgroundBrush);
    painter.drawRoundedRect(0, 0, m_currX + m_R, height(), m_R, m_R);

    // 绘制右边进度条
    painter.setBrush(m_offBackgroundBrush);
    painter.drawRoundedRect(m_currX - m_R, 0, width() - m_currX + m_R, height(), m_R, m_R);

    // 绘制按钮
    painter.setBrush(m_indicatorBrush);
    painter.drawEllipse(QPoint(m_currX, m_R), m_R, m_R);

    painter.setPen(Qt::white);
    painter.setFont(QFont("宋体", 30));
    if (m_currX == m_R) painter.drawText(height(), 0, width() - height(), height(), Qt::AlignCenter, m_offText);
    if (m_currX == width() - m_R) painter.drawText(0, 0, width() - height(), height(), Qt::AlignCenter, m_onText);
}

void MySwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_isOff)
        {
            m_animation->setStartValue(m_R);
            m_animation->setEndValue(width() - m_R);
        }
        else
        {
            m_animation->setStartValue(width() - m_R);
            m_animation->setEndValue(m_R);
        }
        m_isOff = !m_isOff;
        m_animation->start();
    }
}

void MySwitchButton::resizeEvent(QResizeEvent *event)
{
    m_animation->setStartValue(height() / 2);
    m_animation->setEndValue(width() - height() / 2);
    m_R = height() / 2;
}
