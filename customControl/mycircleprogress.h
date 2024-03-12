#ifndef MYCIRCLEPROGRESS_H
#define MYCIRCLEPROGRESS_H

#include <QWidget>
#include <QPropertyAnimation>

class MyCircleProgress : public QWidget
{
    Q_OBJECT
public:
    explicit MyCircleProgress(QWidget *parent = nullptr);

private:
    void paintGray(QPainter& painter);
    void paintProgress(QPainter& painter);
    void paintText(QPainter& painter);

public slots:
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    int m_outR;
    int m_inR;
    int m_value;
    int m_currProgress;

    QPainter* m_painter;
    QPropertyAnimation* m_animation;    // 动画
};

#endif // MYCIRCLEPROGRESS_H
