#include "unlockinterface.h"

#include <QLabel>

UnLockInterface::UnLockInterface(QWidget *parent)
    : QWidget{parent}
{
    QLabel unLock_text("已解锁", this);
}
