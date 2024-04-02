#ifndef CHECKFACESTART_H
#define CHECKFACESTART_H

#include <QWidget>

class QPushButton;

class CheckFaceStart : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFaceStart(QWidget *parent = nullptr);

signals:
    void signUp();
    void signIn();

private:
    QPushButton* m_signUp;
    QPushButton* m_signIn;

};

#endif // CHECKFACESTART_H
