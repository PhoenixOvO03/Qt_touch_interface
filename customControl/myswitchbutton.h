#ifndef MYSWITCHBUTTON_H
#define MYSWITCHBUTTON_H

#include <QWidget>
#include <QPropertyAnimation>

class MySwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit MySwitchButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

signals:    

private:
    bool m_isOff;
    int m_currX;
    int m_R;

    QBrush m_offBackgroundBrush;
    QBrush m_onBackgroundBrush;

    QBrush m_indicatorBrush;

    QString m_offText;
    QString m_onText;

    QPropertyAnimation* m_animation;
};

#endif // MYSWITCHBUTTON_H
