TEMPLATE = app
TARGET = demo
DESTDIR = ../bin

QT += gui widgets

OBJECTS_DIR = obj
RCC_DIR = obj
UI_DIR = obj
MOC_DIR = obj

LIBS += -L../lib -L../lib/gis -lmap2 -lmapacces

INCLUDEPATH += ../include

# Input
HEADERS += mainwindow.h
FORMS += mainwindow.ui
SOURCES += main.cpp mainwindow.cpp

RESOURCES += \
    ../res.qrc
