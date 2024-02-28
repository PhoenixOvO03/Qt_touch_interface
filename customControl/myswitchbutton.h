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
    bool m_isOff;   // 是否关闭
    int m_currX;    // 当前圆点位置
    int m_R;        // 半径

    QString m_offText;  // 关闭文字
    QString m_onText;   // 开启文字

    QPropertyAnimation* m_animation;    // 动画
};

#endif // MYSWITCHBUTTON_H
