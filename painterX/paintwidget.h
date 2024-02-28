#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPen>

class QPen;

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    enum Shape{
        Point_,         // 点
        Line_,          // 线

        Rect_,          // 矩形
        RoundedRect_,   // 圆角矩形
        Ellipse_,       // 椭圆

        Polyline_,      // 多段线
        Polygon_,       // 多边形

        Arc_,           // 圆弧
        Pie_,           // 饼图
        Chord_,         // 弦图

        Path_,          // 路径

        Text_,          // 文本
        Pixmap_,        // 图片
    };

public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void setShape(Shape shape); // 设置形状
    void setPen(QPen pen);      // 设置画笔
    void setBrush(QColor color, Qt::BrushStyle style);  // 设置笔刷
    void setAntialias(bool antialias);  // 设置抗锯齿
    void setTransform(bool transform);  // 设置变换形状

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    Shape m_shape;      // 绘制形状
    QPen m_pen;         // 画笔
    QBrush m_brush;     // 笔刷
    bool m_antialias;   // 抗锯齿
    bool m_transform;   // 变换
};

#endif // PAINTWIDGET_H
