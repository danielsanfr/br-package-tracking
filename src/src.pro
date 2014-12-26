QT       += core network

CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

TARGET = packagetracking

SOURCES += \
    util/downloadhtml.cpp \
    util/util.cpp \
    package.cpp \
    checkpoint.cpp \
    brpostofficeprovider.cpp

HEADERS += \
    util/downloadhtml.h \
    util/util.h \
    package.h \
    checkpoint.h \
    shippingcarrierprovider.h \
    brpostofficeprovider.h

include(../defaults.pri)
