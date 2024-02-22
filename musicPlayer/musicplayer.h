#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "software.h"

#include <QPushButton>
#include <QListWidget>
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QVector>
#include <QLabel>

class musicPlayer : public Software
{
    Q_OBJECT
public:
    explicit musicPlayer(Software *parent = nullptr);

    void interfaceInit();

signals:

private:
    QPushButton* m_file;    // 文件
    QPushButton* m_list;    // 列表
    QPushButton* m_prev;    // 上一曲
    QPushButton* m_pause;   // 暂停
    QPushButton* m_next;    // 下一曲
    QPushButton* m_volume;  // 音量

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
