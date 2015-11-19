#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T13:42:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rankings
TEMPLATE = app


SOURCES += main.cpp \
    leaderboard.cpp \
    sqlhandler.cpp

HEADERS  += \
    leaderboard.h \
    sqlhandler.h

FORMS    += \
    leaderboard.ui

RESOURCES += \
    anderenaam.qrc
