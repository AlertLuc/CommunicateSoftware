#-------------------------------------------------
#
# Project created by QtCreator 2022-05-27T23:24:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




TARGET = IMClient
TEMPLATE = app

INCLUDEPATH += ./net
INCLUDEPATH += ./mediator

INCLUDEPATH += ./histogramwidget
INCLUDEPATH += ./player
INCLUDEPATH += ./playercontrols
INCLUDEPATH += ./playlistmodel
INCLUDEPATH += ./videowidget



LIBS += -lws2_32


SOURCES += main.cpp\
        mychatdialog.cpp \
    net/TcpClientNet.cpp \
    mediator/INetMediator.cpp\
    mediator/TcpClientMediator.cpp \
    net/INet.cpp \
    ckernel.cpp \
    logindialog.cpp \
    useritem.cpp \
    chatdialog.cpp \
    mainwindow.cpp \
    game.cpp

HEADERS  += mychatdialog.h \
    net/INet.h \
    net/packDef.h \
    net/TcpClientNet.h \
    mediator/INetMediator.h \
    mediator/TcpClientMediator.h \
    ckernel.h \
    logindialog.h \
    useritem.h \
    chatdialog.h \
    mainwindow.h \
    game.h
FORMS    += mychatdialog.ui \
    logindialog.ui \
    useritem.ui \
    chatdialog.ui \
    mainwindow.ui \
    game.ui
RESOURCES += \
    resource.qrc

RC_ICONS = logo.ico





