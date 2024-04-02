#ifndef CHECKFACESIGNUP_H
#define CHECKFACESIGNUP_H

#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
class VideoLabel;

class CheckFaceSignUp : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFaceSignUp(QWidget *parent = nullptr);

    void interfaceInit();
    void connectInit();

signals:
    void returnBack();

private slots:
    void openCamera();//打开摄像头
    void closeCamera();//关闭摄像头

private:
    QLineEdit* m_nameEdit;

    QPushButton* m_openBtn;
    QPushButton* m_closeBtn;
    QPushButton* m_signUpBtn;
    QPushButton* m_returnBtn;

    VideoLabel* m_videoLabel;

};

#endif // CHECKFACESIGNUP_H
