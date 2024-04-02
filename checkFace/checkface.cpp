#include "checkface.h"
#include "checkfacestart.h"
#include "checkfacesignin.h"
#include "checkfacesignup.h"

CheckFace::CheckFace(QWidget *parent)
    : Software{parent}
{
    m_unLock = nullptr;

    m_start = new CheckFaceStart(this);
    m_signIn = new CheckFaceSignIn(this);
    m_signUp = new CheckFaceSignUp(this);
    m_signIn->hide();
    m_signUp->hide();

    connect(m_start, &CheckFaceStart::signIn, this, [&](){
        m_start->hide();
        m_signIn->show();
    });

    connect(m_start, &CheckFaceStart::signUp, this, [&](){
        m_start->hide();
        m_signUp->show();
    });

    connect(m_signIn, &CheckFaceSignIn::returnBack, this, [&](){
        m_signIn->hide();
        m_start->show();
    });

    connect(m_signUp, &CheckFaceSignUp::returnBack, this, [&](){
        m_signUp->hide();
        m_start->show();
    });
}
