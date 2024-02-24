#ifndef SERIALCOMBOBOX_H
#define SERIALCOMBOBOX_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QStringList>

class SerialComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit SerialComboBox(QWidget *parent = nullptr);
    explicit SerialComboBox(QString name, QWidget *parent = nullptr);

    QString currentText();
    void setItems(QStringList& items);

signals:

private:
    QLabel* m_label;
    QComboBox* m_comboBox;
};

#endif // SERIALCOMBOBOX_H
