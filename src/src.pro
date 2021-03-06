QT       += core network

CONFIG   += console
CONFIG   -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): \
    QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

TARGET = brpackagetracking

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

RESOURCES += \
    xml.qrc

include(../defaults.pri)
