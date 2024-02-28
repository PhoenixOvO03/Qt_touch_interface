#ifndef MYSLIDERHUNDRED_H
#define MYSLIDERHUNDRED_H

#include <QWidget>

class MySliderHundred : public QWidget
{
    Q_OBJECT
public:
    explicit MySliderHundred(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousereleaveEvent(QMouseEvent* event);

signals:
    void valueChanged(int value);

private:
    int m_value;    // 当前进度
    int m_currX;    // 按钮位置
    int m_R;        // 半径
    bool m_hold;    // 是否按住
};

#endif // MYSLIDERHUNDRED_H
