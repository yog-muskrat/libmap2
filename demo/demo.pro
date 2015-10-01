TEMPLATE = app
TARGET = demo
DESTDIR = ../bin

QT += gui

greaterThan(QT_MAJOR_VERSION, 4)
{
  QT += widgets x11extras
}

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
