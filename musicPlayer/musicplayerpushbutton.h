#ifndef MUSICPLAYERPUSHBUTTON_H
#define MUSICPLAYERPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MusicPlayerPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MusicPlayerPushButton(QWidget *parent = nullptr);
    explicit MusicPlayerPushButton(QString type, QWidget *parent = nullptr);

signals:
};

#endif // MUSICPLAYERPUSHBUTTON_H
