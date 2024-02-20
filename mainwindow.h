#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "app.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>

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

private:
    Ui::MainWindow *ui;

    QVBoxLayout* m_allApp;
    QHBoxLayout* m_firstFloor;
    QHBoxLayout* m_secondFloor;
    QHBoxLayout* m_thirdFllor;
};
#endif // MAINWINDOW_H
