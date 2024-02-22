#include "musicplayer.h"

#include <QFileDialog>
#include <QDir>

musicPlayer::musicPlayer(Software *parent)
    : Software{parent}
{
    interfaceInit();

    m_currentPlayIndex = 0;

    m_output = new QAudioOutput(this);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_output);

    m_currentTime = new QLabel("00:00", this);
    m_currentTime->move(50, 470);
    m_allTime = new QLabel("00:00", this);
    m_allTime->move(720, 470);

    connect(m_player, &QMediaPlayer::durationChanged, [&](qint64 duration){
        m_allTime->setText(QString("%1:%2").arg(duration/1000/60, 2, 10, QChar('0')).arg(duration/1000 % 60, 2, 10, QChar('0')));
        m_musicProgress->setRange(0,duration);
    });

    connect(m_player, &QMediaPlayer::positionChanged, [&](qint64 pos){
        m_currentTime->setText(QString("%1:%2").arg(pos/1000/60, 2, 10, QChar('0')).arg(pos/1000 % 60, 2, 10, QChar('0')));
        m_musicProgress->setValue(pos);
    });

    connect(m_musicProgress, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
}

void musicPlayer::interfaceInit()
{
    this->setFixedSize(800, 600);

    m_musicList = new QListWidget(this);
    m_musicList->setFixedSize(700,400);
    m_musicList->move(50,50);

    m_file = new QPushButton(this);
    m_file->setFixedSize(50, 50);
    m_file->setIconSize(QSize(50, 50));
    m_file->setIcon(QIcon(":/img/file.png"));
    m_file->move(50, 500);

    m_list = new QPushButton(this);
    m_list->setFixedSize(50, 50);
    m_list->setIconSize(QSize(50, 50));
    m_list->setIcon(QIcon(":/img/menu.png"));
    m_list->move(150, 500);

    m_prev = new QPushButton(this);
    m_prev->setFixedSize(50, 50);
    m_prev->setIconSize(QSize(50, 50));
    m_prev->setIcon(QIcon(":/img/prev.png"));
    m_prev->move(250, 500);

    m_pause = new QPushButton(this);
    m_pause->setFixedSize(50, 50);
    m_pause->setIconSize(QSize(50, 50));
    m_pause->setIcon(QIcon(":/img/pause.png"));
    m_pause->move(350, 500);

    m_next = new QPushButton(this);
    m_next->setFixedSize(50, 50);
    m_next->setIconSize(QSize(50, 50));
    m_next->setIcon(QIcon(":/img/next.png"));
    m_next->move(450, 500);

    m_volume = new QPushButton(this);
    m_volume->setFixedSize(50, 50);
    m_volume->setIconSize(QSize(50, 50));
    m_volume->setIcon(QIcon(":/img/volume.png"));
    m_volume->move(550, 500);

    m_musicProgress = new QSlider(Qt::Horizontal, this);
    m_musicProgress->setFixedWidth(600);
    m_musicProgress->move(100,470);

    // m_volumeProgress = new QSlider(Qt::Vertical, this);
    // m_volumeProgress->setFixedHeight(100);
    // m_volumeProgress->move(550, 400);

    connect(m_file, &QPushButton::clicked, [&](){
        QString path = QFileDialog::getExistingDirectory(this, "请选择音乐所在的目录", "../");
        QDir dir(path);
        QStringList musicList = dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
        m_musicList->addItems(musicList);
        m_musicList->setCurrentRow(0);

        for (QString file : musicList)
        {
            m_playList.append(QUrl::fromLocalFile(path + "/" + file));
        }
    });

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

    connect(m_prev, &QPushButton::clicked, [&](){
        m_currentPlayIndex = (m_currentPlayIndex + m_playList.size() - 1) % m_playList.size();
        m_musicList->setCurrentRow(m_currentPlayIndex);
        m_player->setSource(m_playList[m_currentPlayIndex]);
        m_player->play();
    });

    connect(m_next, &QPushButton::clicked, [&](){
        m_currentPlayIndex = (m_currentPlayIndex + 1) % m_playList.size();
        m_musicList->setCurrentRow(m_currentPlayIndex);
        m_player->setSource(m_playList[m_currentPlayIndex]);
        m_player->play();
    });

    connect(m_musicList, &QAbstractItemView::doubleClicked, [&](const QModelIndex &index){
        m_currentPlayIndex = index.row();
        m_player->setSource(m_playList[m_currentPlayIndex]);
        m_player->play();
    });
}
