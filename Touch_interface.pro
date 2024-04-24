QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# opencv4.9.0
INCLUDEPATH += C:\Users\29853\Documents\tool\opencv\build\include
# INCLUDEPATH += C:\Users\29853\Documents\tool\opencv\release\bin
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_core490.dll
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_highgui490.dll
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_imgcodecs490.dll
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_imgproc490.dll
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_calib3d490.dll
LIBS += C:\Users\29853\Documents\tool\opencv\release\bin\libopencv_videoio490.dll

INCLUDEPATH += $$PWD/serialhelper/
INCLUDEPATH += $$PWD/view/
INCLUDEPATH += $$PWD/musicPlayer/
INCLUDEPATH += $$PWD/painterX/
INCLUDEPATH += $$PWD/customControl/
INCLUDEPATH += $$PWD/checkFace/

include($$PWD/serialhelper/serialhelper.pri)
include($$PWD/view/view.pri)
include($$PWD/musicPlayer/musicPlayer.pri)
include($$PWD/painterX/painterX.pri)
include($$PWD/customControl/customControl.pri)
include($$PWD/checkFace/checkFace.pri)

SOURCES += \
    main.cpp

HEADERS +=

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    README.md
