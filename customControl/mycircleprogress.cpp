#include "mycircleprogress.h"

#include <QPainter>
#include <QPainterPath>

MyCircleProgress::MyCircleProgress(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);

    m_outR = 100;
    m_inR = 75;
    m_value = 0;
    m_currProgress = 0;

    m_animation = new QPropertyAnimation(this);
    m_animation->setTargetObject(this);
    m_animation->setEasingCurve(QEasingCurve::OutElastic);
    m_animation->setDirection(QVariantAnimation::Forward);
    m_animation->setDuration(1000);

    connect(m_animation, &QPropertyAnimation::valueChanged, [&](const QVariant& value){
        m_currProgress = value.toInt();
        if (m_currProgress < 0) m_currProgress = 0;
        if (m_currProgress > 360) m_currProgress = 360;
        update();
    });
}

void MyCircleProgress::paintGray(QPainter &painter)
{
    painter.save();
    QPainterPath outPath;
    QPainterPath inPath;

    outPath.addEllipse(rect().center(), m_outR, m_outR);
    inPath.addEllipse(rect().center(), m_inR, m_inR);

    painter.setBrush(Qt::gray);
    painter.drawPath(outPath.subtracted(inPath));
    painter.restore();
}

void MyCircleProgress::paintProgress(QPainter &painter)
{
    painter.save();
    QPainterPath outPath(rect().center());
    QPainterPath inPath;

    outPath.arcTo(rect(), 270, -m_currProgress);
    outPath.closeSubpath();
    inPath.addEllipse(rect().center(), m_inR, m_inR);

    painter.setBrush(Qt::blue);
    painter.drawPath(outPath.subtracted(inPath));
    painter.restore();
}

void MyCircleProgress::paintText(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::blue);
    painter.setFont(QFont("华文彩云", 30));
    painter.drawText(0, 0, width(), height(), Qt::AlignCenter, QString::number((int)(m_currProgress/3.6)));
    painter.restore();
}

void MyCircleProgress::setValue(int value)
{
    m_value = value;
    m_animation->stop();
    m_animation->setStartValue(m_currProgress);
    m_animation->setEndValue((int)(value*3.6));
    m_animation->start();
}

void MyCircleProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    paintGray(painter);
    paintProgress(painter);
    paintText(painter);
}
