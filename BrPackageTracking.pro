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
    package.cpp \
    core/htmlparser.cpp \
    core/downloadhtml.cpp \
    util/util.cpp \
    handlerconnect.cpp \
    model/information.cpp

HEADERS += \
    package.h \
    core/htmlparser.h \
    core/downloadhtml.h \
    util/util.h \
    handlerconnect.h \
    model/information.h
