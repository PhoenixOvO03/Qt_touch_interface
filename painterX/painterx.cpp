#include "painterx.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QColorDialog>
#include <QPen>

PainterX::PainterX(QWidget *parent)
    : Software{parent}
{
    interfaceInit();
    itemInit();
    connectInit();
    dataInit();

    shapeChanged(0);
    penChanged();
    brushChanged();
    m_paintWidget->setAntialias(false);
    m_paintWidget->setTransform(false);
}

void PainterX::interfaceInit()
{
    // 图形形状
    QLabel* shapeLabel = new QLabel("图形形状");
    m_shapeComboBox = new QComboBox();

    QHBoxLayout* shapeLayout = new QHBoxLayout();
    shapeLayout->addWidget(shapeLabel);
    shapeLayout->addWidget(m_shapeComboBox);

    // 绘图区域
    m_paintWidget = new PaintWidget();
    QHBoxLayout* centerLayout = new QHBoxLayout();
    centerLayout->addWidget(m_paintWidget);

    // 画笔设置
    QLabel* widthLabel = new QLabel("宽度");
    m_widthSpin = new QSpinBox();
    QLabel* paintColorLable = new QLabel("颜色");
    m_penColorBtn = new QPushButton();
    QLabel* paintStyleLable = new QLabel("样式");
    m_penStyleLCombBox = new QComboBox();
    QLabel* connectLable = new QLabel("连接");
    m_connectCombBox = new QComboBox();
    QLabel* endLable = new QLabel("末端");
    m_endCombBox = new QComboBox();

    QGridLayout* painterLayout = new QGridLayout();
    painterLayout->addWidget(widthLabel, 0,0,1,1);
    painterLayout->addWidget(m_widthSpin,0,1,1,1);
    painterLayout->addWidget(connectLable,0,2,1,1);
    painterLayout->addWidget(m_connectCombBox, 0,3,1,1);
    painterLayout->addWidget(paintColorLable,1,0,1,1);
    painterLayout->addWidget(m_penColorBtn,1,1,1,1);
    painterLayout->addWidget(endLable,1,2,1,1);
    painterLayout->addWidget(m_endCombBox,1,3,1,1);
    painterLayout->addWidget(paintStyleLable,2,0,1,1);
    painterLayout->addWidget(m_penStyleLCombBox,2,1,1,1);

    QGroupBox* paintBox = new QGroupBox("画笔设置");
    paintBox->setLayout(painterLayout);

    // 画刷设置
    QLabel* brushColorLable = new QLabel("颜色");
    m_brushColorBtn = new QPushButton();
    QLabel* brushStyleLable = new QLabel("样式");
    m_brushStyleLCombBox = new QComboBox();

    QGridLayout* brushLayout = new QGridLayout();
    brushLayout->addWidget(brushColorLable,0,0,1,1);
    brushLayout->addWidget(m_brushColorBtn,0,1,1,1);
    brushLayout->addWidget(brushStyleLable,1,0,1,1);
    brushLayout->addWidget(m_brushStyleLCombBox,1,1,1,1);

    QGroupBox* brushBox = new QGroupBox("画刷设置");
    brushBox->setLayout(brushLayout);

    // 高级选项
    m_change = new QCheckBox("变换（旋转、缩放）");
    m_antiAliasing = new QCheckBox("抗锯齿");

    QVBoxLayout* moreSettingLayout = new QVBoxLayout();
    moreSettingLayout->addWidget(m_change);
    moreSettingLayout->addWidget(m_antiAliasing);

    QGroupBox* moreSetting = new QGroupBox("高级选项");
    moreSetting->setLayout(moreSettingLayout);

    // 下方
    QHBoxLayout* bottonLayout = new QHBoxLayout();
    bottonLayout->addWidget(paintBox);
    bottonLayout->addWidget(brushBox);
    bottonLayout->addWidget(moreSetting);

    // 所有
    QVBoxLayout* allwidget = new QVBoxLayout(this);
    allwidget->addLayout(shapeLayout);
    allwidget->addLayout(centerLayout);
    allwidget->addLayout(bottonLayout);
}

void PainterX::itemInit()
{
    // 形状
    m_shapeComboBox->addItem("点", static_cast<int>(Shape::Point_));
    m_shapeComboBox->addItem("线", static_cast<int>(Shape::Line_));
    m_shapeComboBox->addItem("矩形", static_cast<int>(Shape::Rect_));
    m_shapeComboBox->addItem("圆角矩形", static_cast<int>(Shape::RoundedRect_));
    m_shapeComboBox->addItem("椭圆", static_cast<int>(Shape::Ellipse_));
    m_shapeComboBox->addItem("多边线", static_cast<int>(Shape::Polyline_));
    m_shapeComboBox->addItem("多边形", static_cast<int>(Shape::Polygon_));
    m_shapeComboBox->addItem("圆弧", static_cast<int>(Shape::Arc_));
    m_shapeComboBox->addItem("饼图", static_cast<int>(Shape::Pie_));
    m_shapeComboBox->addItem("弦图", static_cast<int>(Shape::Chord_));
    m_shapeComboBox->addItem("贝瑟尔曲线", static_cast<int>(Shape::Path_));
    m_shapeComboBox->addItem("文本", static_cast<int>(Shape::Text_));
    m_shapeComboBox->addItem("图片", static_cast<int>(Shape::Pixmap_));

    // 宽度
    m_widthSpin->setRange(1, 10);

    // 线的形状
    m_penStyleLCombBox->addItem("实线", static_cast<int>(Qt::SolidLine));
    m_penStyleLCombBox->addItem("虚线", static_cast<int>(Qt::DashLine));
    m_penStyleLCombBox->addItem("点线", static_cast<int>(Qt::DotLine));
    m_penStyleLCombBox->addItem("虚线和点", static_cast<int>(Qt::DashDotLine));
    m_penStyleLCombBox->addItem("虚线和两个点", static_cast<int>(Qt::DashDotDotLine));
    m_penStyleLCombBox->addItem("无", static_cast<int>(Qt::CustomDashLine));

    // 连接
    m_connectCombBox->addItem("Miter", static_cast<int>(Qt::MiterJoin));
    m_connectCombBox->addItem("Bevel", static_cast<int>(Qt::BevelJoin));
    m_connectCombBox->addItem("Round", static_cast<int>(Qt::RoundJoin));

    // 末端
    m_endCombBox->addItem("Flat", static_cast<int>(Qt::FlatCap));
    m_endCombBox->addItem("Square", static_cast<int>(Qt::SquareCap));
    m_endCombBox->addItem("Round", static_cast<int>(Qt::RoundCap));

    // 画刷
    m_brushStyleLCombBox->addItem(tr("Linear Gradient"), static_cast<int>(Qt::LinearGradientPattern));
    m_brushStyleLCombBox->addItem(tr("Radial Gradient"), static_cast<int>(Qt::RadialGradientPattern));
    m_brushStyleLCombBox->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
    m_brushStyleLCombBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    m_brushStyleLCombBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    m_brushStyleLCombBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    m_brushStyleLCombBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    m_brushStyleLCombBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    m_brushStyleLCombBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    m_brushStyleLCombBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    m_brushStyleLCombBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    m_brushStyleLCombBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    m_brushStyleLCombBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    m_brushStyleLCombBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
}

void PainterX::connectInit()
{
    // 形状
    connect(m_shapeComboBox, &QComboBox::currentIndexChanged, this, &PainterX::shapeChanged);
    // 画笔设置
    connect(m_widthSpin, &QSpinBox::valueChanged, this, &PainterX::penChanged);
    connect(m_penColorBtn, &QPushButton::clicked, this, &PainterX::colorChanged);
    connect(m_penStyleLCombBox, &QComboBox::activated, this, &PainterX::penChanged);
    connect(m_connectCombBox, &QComboBox::activated, this, &PainterX::penChanged);
    connect(m_endCombBox, &QComboBox::activated, this, &PainterX::penChanged);
    // 笔刷设置
    connect(m_brushColorBtn, &QPushButton::clicked, this, &PainterX::brushColorChanged);
    connect(m_brushStyleLCombBox, &QComboBox::activated, this, &PainterX::brushChanged);
    // 高级选项
    // connect(m_antiAliasing, &QCheckBox::toggled, this, &PainterX::antialiasChanged);
    connect(m_antiAliasing, &QCheckBox::toggled, m_paintWidget, &PaintWidget::setAntialias);
    connect(m_change, &QCheckBox::toggled, m_paintWidget, &PaintWidget::setTransform);
}

void PainterX::dataInit()
{
    QPalette pal = m_penColorBtn->palette();
    pal.setColor(QPalette::Button, QColor(0,0,0));
    m_penColorBtn->setPalette(pal);
    m_penColorBtn->setAutoFillBackground(true);
    m_penColorBtn->setFlat(true);

    m_brushColorBtn->setPalette(pal);
    m_brushColorBtn->setAutoFillBackground(true);
    m_brushColorBtn->setFlat(true);
}

void PainterX::shapeChanged(int index)
{
    Shape shape = (Shape)m_shapeComboBox->itemData(index).toInt();
    m_paintWidget->setShape(shape);
}

void PainterX::penChanged()
{
    int width = m_widthSpin->value();
    QColor color = m_penColorBtn->palette().color(QPalette::Button);
    Qt::PenStyle penStyle = (Qt::PenStyle)m_penStyleLCombBox->itemData(m_penStyleLCombBox->currentIndex()).toInt();
    Qt::PenCapStyle end = (Qt::PenCapStyle)m_endCombBox->itemData(m_endCombBox->currentIndex()).toInt();
    Qt::PenJoinStyle connect = (Qt::PenJoinStyle)m_connectCombBox->itemData(m_connectCombBox->currentIndex()).toInt();

    m_paintWidget->setPen(QPen(color, width, penStyle, end, connect));
}

void PainterX::colorChanged()
{
    QColor color = QColorDialog::getColor(QColor(255,255,255), this, "画笔颜色");
    if (!color.isValid())return;
    QPalette pal = m_penColorBtn->palette();
    pal.setColor(QPalette::Button, color);
    m_penColorBtn->setPalette(pal);
    m_penColorBtn->setAutoFillBackground(true);
    m_penColorBtn->setFlat(true);

    penChanged();
}

void PainterX::brushColorChanged()
{
    QColor color = QColorDialog::getColor(QColor(255,255,255), this, "画笔颜色");
    if (!color.isValid())return;
    QPalette pal = m_brushColorBtn->palette();
    pal.setColor(QPalette::Button, color);

    brushChanged();
}

void PainterX::brushChanged()
{
    QColor color = m_brushColorBtn->palette().color(QPalette::Button);
    Qt::BrushStyle style = (Qt::BrushStyle)m_brushStyleLCombBox->itemData(m_brushStyleLCombBox->currentIndex()).toInt();
    m_paintWidget->setBrush(color, style);
}

