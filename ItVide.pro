#-------------------------------------------------
#
# Project created by QtCreator 2013-02-08T15:34:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ItVide
VERSION = 0.9.0.0
TEMPLATE = app
CONFIG += c++11
DEFINES += MYSOFTWARE=\\\"$$TARGET\\\"
DEFINES += MYVERSION=\\\"$$VERSION\\\"
DEFINES += GIT_VERSION=\\\"$$system(git describe --always)\\\"

VPATH+=$$EXTERNAL_PATH
INCLUDEPATH+=$$EXTERNAL_PATH

SOURCES += main.cpp\
        mainwindow.cpp \
    importwindow.cpp \
    datamatrix.cpp \
    datatable.cpp \
    widgetlist.cpp \
    rangeslider.cpp \
    qcustomplot.cpp \
    setchartcolor.cpp \
    plotdatacontainer.cpp \
    setchartparameter.cpp

HEADERS  += mainwindow.h \
    importwindow.h \
    datamatrix.h \
    datatable.h \
    global.h \
    widgetlist.h \
    messages.h \
    rangeslider.h \
    qcustomplot.h \
    setchartcolor.h \
    plotdatacontainer.h \
    setchartparameter.h

FORMS    += mainwindow.ui \
    importwindow.ui \
    setchartcolor.ui \
    setchartparameter.ui

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR

DISTFILES +=

