#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T18:15:03
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CityGIS
TEMPLATE = app


SOURCES += main.cpp \
    auth.cpp \
    reg.cpp \
    mainwindow.cpp

HEADERS  += \
    gisdatabase.h \
    auth.h \
    reg.h \
    mainwindow.h \
    viewport.h \

FORMS += \
    auth.ui \
    reg.ui \
    mainwindow.ui

DISTFILES +=
