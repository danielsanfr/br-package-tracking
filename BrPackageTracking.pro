#-------------------------------------------------
#
# Project created by QtCreator 2014-03-02T23:07:48
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = BrPackageTracking
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    packageinfomodel.cpp \
    package.cpp \
    htmlparser.cpp \
    downloadhtml.cpp \
    util.cpp \
    handlerconnect.cpp

HEADERS += \
    packageinfomodel.h \
    package.h \
    htmlparser.h \
    downloadhtml.h \
    util.h \
    handlerconnect.h
