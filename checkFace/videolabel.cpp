#include "videolabel.h"

#include <QLabel>
#include <QTimer>
#include <QBrush>
#include <QVBoxLayout>
#include <QHBoxLayout>

VideoLabel::VideoLabel(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(650, 450);

    m_video_label = new QLabel();

    QHBoxLayout* allLayout = new QHBoxLayout(this);
    allLayout->addWidget(m_video_label);

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&VideoLabel::readFrame);//超时就捕捉一张图片
}

QImage VideoLabel::Mat2QImage(const Mat &mat)//mat转QImage
{
    if(mat.type()==CV_8UC1)
    {
        QVector<QRgb>colorTable;
        for(int i=0;i<256;i++)
            colorTable.push_back(qRgb(i,i,i));
        const uchar*qImageBuffer=(const uchar*)mat.data;
        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    //8-bitsunsigned,NO.OFCHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        const uchar* qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
        return img.rgbSwapped();
    }

    return QImage();
}

void VideoLabel::openCamera() //打开摄像头
{
    m_cam.open(0);
    m_timer->start(33);        // 开始计时
}

void VideoLabel::closeCamera()//关闭摄像头
{
    m_cam.release();
    m_timer->stop();
    readFrame();
}

void VideoLabel::readFrame() //读取帧并显示
{
    m_cam >> m_frame;
    m_imag = Mat2QImage(m_frame);
    m_video_label->setPixmap(QPixmap::fromImage(m_imag));
}
