#ifndef PAINTERX_H
#define PAINTERX_H

#include "software.h"

class QComboBox;
class QSpinBox;
class QPushButton;
class QCheckBox;
class PaintWidget;

class PainterX : public Software
{
    Q_OBJECT
public:
    explicit PainterX(QWidget *parent = nullptr);

    void interfaceInit();   // 界面初始化
    void itemInit();        // combobox数据初始化
    void connectInit();     // connect函数初始化
    void dataInit();        // 数据初始化

signals:

private slots:
    void shapeChanged(int index);   // 绘制图案更改
    void penChanged();              // 画笔更改
    void colorChanged();            // 画笔颜色更改

    void brushColorChanged();       // 笔刷颜色更改
    void brushChanged();            // 笔刷更改

private:
    QComboBox* m_shapeComboBox; // 图形形状

    PaintWidget* m_paintWidget; // 绘图区域

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
