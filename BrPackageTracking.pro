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

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    src/util/downloadhtml.cpp \
    src/util/util.cpp \
    src/package.cpp \
    src/checkpoint.cpp \
    src/brpostofficeprovider.cpp

HEADERS += \
    src/util/downloadhtml.h \
    src/util/util.h \
    src/package.h \
    src/checkpoint.h \
    src/shippingcarrierprovider.h \
    src/brpostofficeprovider.h
