#ifndef APP_H
#define APP_H

#include <QWidget>

class Software;
class QLabel;
class QPushButton;

class App : public QWidget
{
    Q_OBJECT
public:
    explicit App(QWidget *parent = nullptr);
    explicit App(const QString& name, QWidget *parent = nullptr);

signals:
    void hover(QString arg);
    void clicked(Software* app, QString name, QIcon icon);

protected:
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);

private:
    QLabel* m_name; // app名字
    QPushButton* m_appBtn;  // app按钮
    QString m_description;  // app描述
};

#endif // APP_H
