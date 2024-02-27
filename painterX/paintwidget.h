#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPen>

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

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void setShape(Shape shape);
    void setPen(QPen pen);
    void setBrush(QColor color, Qt::BrushStyle style);
    void setAntialias(bool antialias);
    void setTransform(bool transform);

protected:
    void extracted();
    void paintEvent(QPaintEvent *event);

signals:

private:
    Shape m_shape;
    QPen m_pen;
    QBrush m_brush;
    bool m_antialias;
    bool m_transform;
};

#endif // PAINTWIDGET_H
