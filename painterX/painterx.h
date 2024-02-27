#ifndef PAINTERX_H
#define PAINTERX_H

#include "software.h"
#include "paintwidget.h"

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

class PainterX : public Software
{
    Q_OBJECT
public:
    explicit PainterX(QWidget *parent = nullptr);

    void interfaceInit();
    void itemInit();
    void connectInit();
    void dataInit();

signals:

private slots:
    void shapeChanged(int index);
    void penChanged();
    void colorChanged();

    void brushColorChanged();
    void brushChanged();

private:
    // 图形形状
    QComboBox* m_shapeComboBox;

    // 绘图区域
    PaintWidget* m_paintWidget;

    // 画笔设置
    QSpinBox* m_widthSpin;
    QPushButton* m_penColorBtn;
    QComboBox* m_penStyleLCombBox;
    QComboBox* m_connectCombBox;
    QComboBox* m_endCombBox;

    // 画刷设置
    QPushButton* m_brushColorBtn;
    QComboBox* m_brushStyleLCombBox;

    // 高级选项
    QCheckBox* m_change;
    QCheckBox* m_antiAliasing;
};

#endif // PAINTERX_H
