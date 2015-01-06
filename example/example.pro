QT += core network
QT -= gui

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += main.cpp

LIBS += -L../src -lbrpackagetracking

include(../defaults.pri)
