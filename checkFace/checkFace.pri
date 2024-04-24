INCLUDEPATH += $$PWD/face_SDK/inc

LIBS += $$PWD/face_SDK/lib/X64/libarcsoft_face.dll
LIBS += $$PWD/face_SDK/lib/X64/libarcsoft_face_engine.dll
LIBS += $$PWD/face_SDK/lib/X64/libarcsoft_face_engine.lib

HEADERS += \
    $$PWD/checkface.h \
    $$PWD/checkfacesignin.h \
    $$PWD/checkfacesignup.h \
    $$PWD/checkfacestart.h \
    $$PWD/unlockinterface.h \
    $$PWD/videolabel.h

SOURCES += \
    $$PWD/checkface.cpp \
    $$PWD/checkfacesignin.cpp \
    $$PWD/checkfacesignup.cpp \
    $$PWD/checkfacestart.cpp \
    $$PWD/unlockinterface.cpp \
    $$PWD/videolabel.cpp
