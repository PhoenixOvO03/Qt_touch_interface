#include "musicplayerpushbutton.h"

MusicPlayerPushButton::MusicPlayerPushButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setFixedSize(50, 50);
    this->setIconSize(QSize(50, 50));
}

MusicPlayerPushButton::MusicPlayerPushButton(QString type, QWidget *parent)
    : MusicPlayerPushButton(parent)
{
    // 根据名字设置图标
    if (type == "文件")
    {
        this->setIcon(QIcon(":/img/file.png"));
    }
    else if (type == "菜单")
    {
        this->setIcon(QIcon(":/img/menu.png"));
    }
    else if (type == "上一曲")
    {
        this->setIcon(QIcon(":/img/prev.png"));
    }
    else if (type == "播放")
    {
        this->setIcon(QIcon(":/img/pause.png"));
    }
    else if (type == "下一曲")
    {
        this->setIcon(QIcon(":/img/next.png"));
    }
    else if (type == "音量")
    {
        this->setIcon(QIcon(":/img/volume.png"));
    }
}
