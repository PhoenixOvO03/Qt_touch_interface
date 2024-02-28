#ifndef SERIALCOMBOBOX_H
#define SERIALCOMBOBOX_H

#include <QWidget>

class QLabel;
class QComboBox;

class SerialComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit SerialComboBox(QWidget *parent = nullptr);
    explicit SerialComboBox(QString name, QWidget *parent = nullptr);

    QString currentText();  // 当前显示内容
    void setItems(QStringList& items);  // combobox添加项目

signals:

private:
    QLabel* m_label;    // 项目名称
    QComboBox* m_comboBox;  // combobox对象
};

#endif // SERIALCOMBOBOX_H
