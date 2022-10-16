#-------------------------------------------------
#
# Project created by QtCreator 2022-07-15T19:12:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQ
TEMPLATE = app

INCLUDEPATH += ./net
INCLUDEPATH += ./mediator

LIBS +=-lws2_32

SOURCES += main.cpp\
        qqdialog.cpp \
    net/TcpClientNet.cpp \
    mediator/INetMediator.cpp \
    mediator/TcpClientMediator.cpp \
    ckernel.cpp \
    logindialog.cpp \
    useritem.cpp \
    chatdialog.cpp

HEADERS  += qqdialog.h \
    net/INet.h \
    net/packDef.h \
    net/TcpClientNet.h \
    mediator/INetMediator.h \
    mediator/TcpClientMediator.h \
    ckernel.h \
    logindialog.h \
    useritem.h \
    chatdialog.h

FORMS    += qqdialog.ui \
    logindialog.ui \
    useritem.ui \
    chatdialog.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    images/1.jpg \
    images/bold.png \
    images/cancel.png \
    images/clear.png \
    images/color.png \
    images/down.png \
    images/folders.png \
    images/font.png \
    images/groupChat 2.png \
    images/hat.png \
    images/Help.png \
    images/history.png \
    images/ic_max_huanyuan.png \
    images/ic_max_zuida.png \
    images/ic_sysmen.png \
    images/icon1.png \
    images/icon2.png \
    images/message.png \
    images/ok.png \
    images/q151020-01.png \
    images/qq151217-02.png \
    images/QQ×¢²á.png \
    images/quit.png \
    images/register.png \
    images/right.png \
    images/save.png \
    images/searchbox_button.png \
    images/send.png \
    images/sett.png \
    images/share.png \
    images/share_¸±±¾.png \
    images/style.png \
    images/tuer.png \
    images/under.png \
    images/file.ico \
    images/message.ico
