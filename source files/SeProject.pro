#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T15:47:25
#
#-------------------------------------------------

QT       += core gui sql webkit webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeProject
TEMPLATE = app


SOURCES += main.cpp \
    studentwindow.cpp \
    qrocheckbox.cpp \
    sqlhandler.cpp \
    logindialog.cpp \
    docentwindow.cpp \
    createwindow.cpp

HEADERS  += \
    studentwindow.h \
    qrocheckbox.h \
    sqlhandler.h \
    logindialog.h \
    docentwindow.h \
    createwindow.h

FORMS    += \
    studentwindow.ui \
    logindialog.ui \
    docentwindow.ui \
    createwindow.ui

RESOURCES += \
    achievements.qrc
