#-------------------------------------------------
#
# Project created by QtCreator 2014-03-02T23:07:48
#
#-------------------------------------------------

TEMPLATE = subdirs

#CONFIG+=ordered

SUBDIRS = \
    src \
    example

example.depends = src

OTHER_FILES += \
    defaults.pri
