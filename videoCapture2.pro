#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T14:48:22
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoCapture2
TEMPLATE = app


SOURCES += main.cpp\
    GUI/mainwindow.cpp \
    GUI/menubar.cpp \
    GUI/treewidget.cpp \
    GUI/centralwidget.cpp \
    GUI/errorwidget.cpp \
    GUI/Dialog/openserverdialog.cpp \
    GUI/Dialog/adddialog.cpp \
    GUI/Dialog/servereditdialog.cpp \
    GUI/Dialog/streameditdialog.cpp \
    GUI/Dialog/formateditdialog.cpp \
    GUI/Dialog/errormessages.cpp \
    config/formattype.cpp \
    config/streamtype.cpp \
    config/servertype.cpp \
    config/cardtype.cpp \
    config/filecontrol.cpp \
    GUI/Dialog/streamiddialog.cpp \
    config/messagetype.cpp \
    GUI/ipelement.cpp \
    GUI/cardelement.cpp \
    GUI/channelelement.cpp \
    thread/messageupdate.cpp \
    thread/timeupdate.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/menubar.h \
    GUI/treewidget.h \
    GUI/centralwidget.h \
    GUI/errorwidget.h \
    GUI/Dialog/openserverdialog.h \
    GUI/Dialog/adddialog.h \
    GUI/Dialog/servereditdialog.h \
    GUI/Dialog/streameditdialog.h \
    GUI/Dialog/formateditdialog.h \
    GUI/Dialog/errormessages.h \
    config/formattype.h \
    config/streamtype.h \
    config/servertype.h \
    config/cardtype.h \
    config/filecontrol.h \
    GUI/Dialog/streamiddialog.h \
    config/messagetype.h \
    GUI/ipelement.h \
    GUI/cardelement.h \
    GUI/channelelement.h \
    thread/messageupdate.h \
    thread/timeupdate.h

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -std=c++11
