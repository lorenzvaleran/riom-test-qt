#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T10:31:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dirspyworker.cpp \
    tablewidget.cpp \
    systemtrayicon.cpp

HEADERS  += mainwindow.h \
    dirspyworker.h \
    tablewidget.h \
    systemtrayicon.h

FORMS    += mainwindow.ui \
    tablewidget.ui

RESOURCES += \
    resourcetest.qrc
