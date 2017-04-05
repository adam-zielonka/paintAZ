#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T11:02:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paintAZ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainwindow.cpp \
    newfiledialog.cpp

HEADERS  += widget.h \
    mainwindow.h \
    newfiledialog.h

FORMS    += widget.ui \
    mainwindow.ui \
    newfiledialog.ui

RESOURCES += \
    resources.qrc
