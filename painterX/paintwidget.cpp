#include "paintwidget.h"

#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(700, 300);
}

void PaintWidget::setShape(Shape shape)
{
    m_shape = shape;
    update();
}

void PaintWidget::setPen(QPen pen)
{
    m_pen = pen;
    update();
}

void PaintWidget::setBrush(QColor color, Qt::BrushStyle style)
{
    if (style == Qt::LinearGradientPattern) // 线性渐变
    {
        QLinearGradient linearGradient(0, 50, 100, 50);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);
        linearGradient.setColorAt(1.0, Qt::black);
        m_brush = linearGradient;
    }
    else if (style == Qt::RadialGradientPattern) // 中心扩散
    {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        m_brush = radialGradient;
    }
    else if (style == Qt::ConicalGradientPattern) // 旋转渐变
    {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        m_brush = conicalGradient;
    }
    else if (style == Qt::TexturePattern) // 纹理材质
    {
        m_brush = QBrush(QPixmap(":/img/brick.png"));
    }
    else
    {
        m_brush = QBrush(color, style);
    }
    update();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    static const QPoint points[4] = {QPoint(10,80), QPoint(20,10), QPoint(80,30), QPoint(90,70)};
    static const QRect rect(10,20,80,60);

    QPainter painter(this);
    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    for (int x = 0; x < width(); x += 100)
    {
        for (int y = 0; y < height(); y += 100)
        {
            painter.save();
            painter.translate(x, y);
            switch (m_shape) {
            case Point_:
                painter.drawPoints(points, 4);
                break;
            case Line_:
                painter.drawLine(points[0], points[2]);
                break;
            case Polyline_:
                painter.drawPolyline(points, 4);
                break;
            case Polygon_:
                painter.drawPolygon(points, 4);
                break;
            case Rect_:
                painter.drawRect(rect);
                break;
            case RoundedRect_:
                painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                break;
            case Ellipse_:
                painter.drawEllipse(rect);
                break;
            default:
                break;
            }
            painter.restore();
        }
    }
}
