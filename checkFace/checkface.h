#ifndef CHECKFACE_H
#define CHECKFACE_H

#include "software.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class QLabel;
class QPushButton;

class CheckFace : public Software
{
    Q_OBJECT
public:
    explicit CheckFace(QWidget *parent = nullptr);

    void interfaceInit();
    void connectInit();

    QImage Mat2QImage(const cv::Mat &mat);

private slots:
    void opencamera();//打开摄像头
    void closecamera();//关闭摄像头
    void readFrame();//读取一帧

private:
    QTimer* m_timer;//计时器
    QImage m_imag;//用QImage形式记录的图片
    cv::VideoCapture m_cam;//视频捕捉
    cv::Mat m_frame;//用mat形式记录的图片

    QPushButton* m_openbtn;
    QPushButton* m_closebtn;

    QLabel* m_video_label;

signals:
};

#endif // CHECKFACE_H
