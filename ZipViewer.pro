#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T11:51:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZipViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

INCLUDEPATH += $$PWD/3rdparty/quazip/include

win32: LIBS += -L$$PWD/3rdparty/quazip/lib -lquazip
win32: LIBS += -L$$PWD/3rdparty/zip -lzlib1

unix: LIBS += -L/lib -lquazip
