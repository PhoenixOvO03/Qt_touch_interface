#ifndef CHECKFACE_H
#define CHECKFACE_H

#include "software.h"

class CheckFaceStart;
class CheckFaceSignIn;
class CheckFaceSignUp;
class UnLockInterface;

class CheckFace : public Software
{
    Q_OBJECT
public:
    explicit CheckFace(QWidget *parent = nullptr);

signals:

private:
    CheckFaceStart* m_start;
    CheckFaceSignIn* m_signIn;
    CheckFaceSignUp* m_signUp;
    UnLockInterface* m_unLock;
};

#endif // CHECKFACE_H
