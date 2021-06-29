QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frameaddtk.cpp \
    framecc.cpp \
    framecpass.cpp \
    framecv.cpp \
    frameinfornv.cpp \
    framekt.cpp \
    framenv.cpp \
    framepb.cpp \
    framesearch.cpp \
    frametkcc.cpp \
    frametl.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp

HEADERS += \
    SQLConnection.h \
    frameaddtk.h \
    framecc.h \
    framecpass.h \
    framecv.h \
    frameinfornv.h \
    framekt.h \
    framenv.h \
    framepb.h \
    framesearch.h \
    frametkcc.h \
    frametl.h \
    login.h \
    mainwindow.h

FORMS += \
    frameaddtk.ui \
    framecc.ui \
    framecpass.ui \
    framecv.ui \
    frameinfornv.ui \
    framekt.ui \
    framenv.ui \
    framepb.ui \
    framesearch.ui \
    frametkcc.ui \
    frametl.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
