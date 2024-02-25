#include "musicplayer.h"

#include <QFileDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>

musicPlayer::musicPlayer(QWidget *parent)
    : Software{parent}
{
    m_currentPlayIndex = 0;
    m_output = new QAudioOutput(this);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_output);

    interfaceInit();
    connectInit();
}

void musicPlayer::interfaceInit()
{
    // 列表窗口
    m_musicList = new QListWidget();
    m_musicList->setFixedSize(700,400);

    QHBoxLayout* musicList = new QHBoxLayout();
    musicList->addStretch(1);
    musicList->addWidget(m_musicList);
    musicList->addStretch(1);

    // 进度条
    m_musicProgress = new QSlider(Qt::Horizontal, this);
    m_currentTime = new QLabel("00:00", this);
    m_allTime = new QLabel("00:00", this);

    QHBoxLayout* musicProgress = new QHBoxLayout();
    musicProgress->addWidget(m_currentTime);
    musicProgress->addWidget(m_musicProgress);
    musicProgress->addWidget(m_allTime);

    // 按钮
    m_file = new MusicPlayerPushButton("文件", this);
    m_list = new MusicPlayerPushButton("菜单", this);
    m_prev = new MusicPlayerPushButton("上一曲", this);
    m_pause = new MusicPlayerPushButton("播放", this);
    m_next = new MusicPlayerPushButton("下一曲", this);
    m_volume = new MusicPlayerPushButton("音量", this);

    QHBoxLayout* Buttons = new QHBoxLayout();
    Buttons->addStretch(1);
    Buttons->addWidget(m_file);
    Buttons->addStretch(1);
    Buttons->addWidget(m_list);
    Buttons->addStretch(1);
    Buttons->addWidget(m_prev);
    Buttons->addStretch(1);
    Buttons->addWidget(m_pause);
    Buttons->addStretch(1);
    Buttons->addWidget(m_next);
    Buttons->addStretch(1);
    Buttons->addWidget(m_volume);
    Buttons->addStretch(1);

    QVBoxLayout* m_allWidget = new QVBoxLayout(this);
    m_allWidget->addStretch(1);
    m_allWidget->addLayout(musicList);
    m_allWidget->addStretch(1);
    m_allWidget->addLayout(musicProgress);
    m_allWidget->addStretch(1);
    m_allWidget->addLayout(Buttons);
    m_allWidget->addStretch(1);

    // 音量滑块
    m_volumeProgress = new QSlider(Qt::Vertical, this);
    m_volumeProgress->setFixedSize(20, 100);
    m_volumeProgress->setRange(0, 100);
    m_volumeProgress->setSliderPosition(100);
    m_volumeProgress->setVisible(false);
}

void musicPlayer::connectInit()
{
    // 文件按钮
    connect(m_file, &QPushButton::clicked, [&](){
        QString path = QFileDialog::getExistingDirectory(this, "请选择音乐所在的目录", "../");
        QDir dir(path);
        QStringList musicList = dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
        m_musicList->setCurrentRow(m_currentPlayIndex);

        for (QString file : musicList)
        {
            QUrl fileUrl = QUrl::fromLocalFile(path + "/" + file);
            if (m_playList.contains(fileUrl) == false)
            {
                m_musicList->addItem(file);
                m_playList.append(fileUrl);
            }
        }
    });

    // 播放按钮
    connect(m_pause, &QPushButton::clicked, [&](){
        if (m_playList.empty())return;
        switch(m_player->playbackState())
        {
        case QMediaPlayer::StoppedState:
        {
            m_currentPlayIndex = m_musicList->currentRow();
            m_player->setSource(m_playList[m_currentPlayIndex]);
            m_player->play();
            break;
        }
        case QMediaPlayer::PlayingState:
        {
            m_player->pause();
            break;
        }
        case QMediaPlayer::PausedState:
        {
            m_player->play();
            break;
        }
        default:
            break;
        }
    });

    // 上一曲
    connect(m_prev, &QPushButton::clicked, this, &musicPlayer::prevMusic);
    // 下一曲
    connect(m_next, &QPushButton::clicked, this, &musicPlayer::nextMusic);

    // 双击播放音乐列表
    connect(m_musicList, &QAbstractItemView::doubleClicked, [&](const QModelIndex &index){
        m_currentPlayIndex = index.row();
        m_player->setSource(m_playList[m_currentPlayIndex]);
        m_player->play();
    });

    // 音量按钮
    connect(m_volume, &QPushButton::clicked, this, &musicPlayer::volumeBtnClicked);

    // 获取播放时长
    connect(m_player, &QMediaPlayer::durationChanged, [&](qint64 duration){
        m_allTime->setText(QString("%1:%2").arg(duration/1000/60, 2, 10, QChar('0')).arg(duration/1000 % 60, 2, 10, QChar('0')));
        m_musicProgress->setRange(0,duration);
    });

    // 更新进度条
    connect(m_player, &QMediaPlayer::positionChanged, [&](qint64 pos){
        m_currentTime->setText(QString("%1:%2").arg(pos/1000/60, 2, 10, QChar('0')).arg(pos/1000 % 60, 2, 10, QChar('0')));
        m_musicProgress->setValue(pos);
    });

    // 拖动进度条
    connect(m_musicProgress, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);

    // 设置音量
    connect(m_volumeProgress, &QSlider::sliderMoved, [&](int position){
        m_output->setVolume(position*1.0 / 100);
    });
}

void musicPlayer::prevMusic()
{
    if (m_playList.empty())return;
    m_currentPlayIndex = (m_currentPlayIndex + m_playList.size() - 1) % m_playList.size();
    m_musicList->setCurrentRow(m_currentPlayIndex);
    m_player->setSource(m_playList[m_currentPlayIndex]);
    m_player->play();
}

void musicPlayer::nextMusic()
{
    if (m_playList.empty())return;
    m_currentPlayIndex = (m_currentPlayIndex + 1) % m_playList.size();
    m_musicList->setCurrentRow(m_currentPlayIndex);
    m_player->setSource(m_playList[m_currentPlayIndex]);
    m_player->play();
}

void musicPlayer::volumeBtnClicked()
{
    QPoint pos = m_volume->pos();
    int x = pos.x() + m_volume->width() / 2 - m_volumeProgress->width() / 2;
    int y = pos.y() - m_volumeProgress->height();
    m_volumeProgress->move(x, y);
    bool visit = m_volumeProgress->isVisible();
    m_volumeProgress->setVisible(!visit);
}
