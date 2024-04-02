#ifndef CHECKFACESIGNIN_H
#define CHECKFACESIGNIN_H

#include <QWidget>

class QPushButton;
class VideoLabel;

class CheckFaceSignIn : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFaceSignIn(QWidget *parent = nullptr);

    void interfaceInit();
    void connectInit();

signals:
    void returnBack();

private slots:
    void openCamera();//打开摄像头
    void closeCamera();//关闭摄像头

private:
    QPushButton* m_openBtn;
    QPushButton* m_closeBtn;
    QPushButton* m_returnBtn;

    VideoLabel* m_videoLabel;
};

#endif // CHECKFACESIGNIN_H
