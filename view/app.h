#ifndef APP_H
#define APP_H

#include "software.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

class App : public QWidget
{
    Q_OBJECT
public:
    explicit App(QWidget *parent = nullptr);
    explicit App(const QString& name, QWidget *parent = nullptr);

signals:
    void pressed(QString arg);
    void clicked(Software* app, QString name, QIcon icon);

private:
    QLabel* m_name; // app名字
    QPushButton* m_appBtn;  // app按钮
    QString m_description;  // app描述
};

#endif // APP_H
