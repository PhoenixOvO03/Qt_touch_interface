#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "software.h"
#include "musicplayerpushbutton.h"

#include <QUrl>

class QAudioOutput;
class QMediaPlayer;
class QLabel;
class QSlider;
class QListWidget;

class musicPlayer : public Software
{
    Q_OBJECT
public:
    explicit musicPlayer(QWidget *parent = nullptr);

    void interfaceInit();   // 界面初始化
    void connectInit();     // connect函数初始化

signals:


private slots:
    void prevMusic();   // 上一曲
    void nextMusic();   // 下一曲
    void volumeBtnClicked();    // 音量按钮

private:
    MusicPlayerPushButton* m_file;    // 文件
    MusicPlayerPushButton* m_list;    // 列表
    MusicPlayerPushButton* m_prev;    // 上一曲
    MusicPlayerPushButton* m_pause;   // 暂停
    MusicPlayerPushButton* m_next;    // 下一曲
    MusicPlayerPushButton* m_volume;  // 音量

    QListWidget* m_musicList;   // 音乐列表

    QSlider* m_musicProgress;   // 进度条
    QSlider* m_volumeProgress;  // 音量条

    QAudioOutput* m_output; // 输出
    QMediaPlayer* m_player; // 媒体播放

    QVector<QUrl> m_playList;   // 播放列表

    int m_currentPlayIndex;
    QLabel* m_currentTime;
    QLabel* m_allTime;
};

#endif // MUSICPLAYER_H
