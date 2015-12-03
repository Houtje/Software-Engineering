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
    docentassignmentswindow.cpp \
    registerwindows.cpp \
    createwindowdialog.cpp \
    form.cpp \
    achievementlist.cpp \
    horizontaldingie.cpp \
    achievementhandler.cpp

HEADERS  += \
    studentwindow.h \
    qrocheckbox.h \
    sqlhandler.h \
    logindialog.h \
    docentwindow.h \
    docentassignmentswindow.h \
    registerwindows.h \
    createwindowdialog.h \
    form.h \
    achievementlist.h \
    horizontaldingie.h \
    achievementhandler.h

FORMS    += \
    studentwindow.ui \
    logindialog.ui \
    docentwindow.ui \
    docentassignmentswindow.ui \
    registerwindows.ui \
    createwindowdialog.ui \
    form.ui \
    achievementlist.ui \
    horizontaldingie.ui

RESOURCES += \
    achievements.qrc
