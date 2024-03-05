#ifndef FUNCTIONBUTTON_H
#define FUNCTIONBUTTON_H

#include <QWidget>

class QLabel;
class QPushButton;
class MainWindow;

class FunctionButton : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionButton(QWidget *parent = nullptr);
    explicit FunctionButton(const QString& name, QWidget *parent = nullptr);

    void function(MainWindow* window);

signals:
    void pressed(QString arg);
    void clicked(FunctionButton* now);

protected:
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);

private:
    QLabel* m_name; // 功能名字
    QPushButton* m_functionBtn;  // 功能按钮
    QString m_description;  // 功能描述
signals:
};

#endif // FUNCTIONBUTTON_H
