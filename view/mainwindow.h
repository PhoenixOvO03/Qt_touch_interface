#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class App;
class Software;
class QVBoxLayout;
class QHBoxLayout;
class FunctionButton;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void hideApps(bool flag);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void appBottonInit();   // 软件按钮初始化
    void functionButtonInit();  // 功能按钮初始化
    void interfaceInit();   // 界面初始化

private:
    Ui::MainWindow *ui;

    bool m_mousePress;  // 按钮是否按下
    QPoint m_pressMousePos;     // 记录鼠标按下鼠标的初始位置
    QPoint m_pressWindowPos;    // 记录鼠标按下窗口的初始位置

    QVector<App*> m_appList;    // 存储所有app
    QVector<FunctionButton*> m_functionBtnList;    // 存储所有的功能按钮

    Software* m_currentApp; // 当前运行的app

    QVBoxLayout* m_allApp;  // 所有app的显示
    QHBoxLayout* m_firstFloor;  // 第一层app
    QHBoxLayout* m_secondFloor; // 第二层app
    QHBoxLayout* m_thirdFllor;  // 第三层app
};
#endif // MAINWINDOW_H
