#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class App;
class Software;
class QVBoxLayout;
class QHBoxLayout;

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

    void appBottonInit();   // 软件按钮初始化
    void interfaceInit();   // 界面初始化

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    QVector<App*> m_appList;    // 存储所有app

    Software* m_currentApp; // 当前运行的app

    QVBoxLayout* m_allApp;  // 所有app的显示
    QHBoxLayout* m_firstFloor;  // 第一层app
    QHBoxLayout* m_secondFloor; // 第二层app
    QHBoxLayout* m_thirdFllor;  // 第三层app
};
#endif // MAINWINDOW_H
