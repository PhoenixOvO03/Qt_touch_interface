#ifndef VIDEOLABEL_H
#define VIDEOLABEL_H

#include <QWidget>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class QLabel;

class VideoLabel : public QWidget
{
    Q_OBJECT
public:
    explicit VideoLabel(QWidget *parent = nullptr);

    QImage Mat2QImage(const cv::Mat &mat);

signals:
    void returnBack();

public slots:
    void openCamera();//打开摄像头
    void closeCamera();//关闭摄像头
    void readFrame();//读取一帧

private:
    QTimer* m_timer;//计时器
    QImage m_imag;//用QImage形式记录的图片
    VideoCapture m_cam;//视频捕捉
    Mat m_frame;//用mat形式记录的图片

    QLabel* m_video_label;

};

#endif // VIDEOLABEL_H
