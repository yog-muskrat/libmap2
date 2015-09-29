TEMPLATE = lib
TARGET = map2
DESTDIR = ../lib
INCLUDEPATH +=	\
			../include \
			../include/map2

OBJECTS_DIR = obj
RCC_DIR = obj
UI_DIR = obj
MOC_DIR = obj

QT += gui widgets

LIBS += -L../lib/gis -l mapacces

HEADERS += mapcanvas.h \
	mapnavigation.h \
	../include/map2/layersmodel.h \
	../include/map2/maplayer.h \
	../include/map2/mapvectorobject.h \
	../include/map2/mapview.h \
	../include/map2/structs.h \
	../include/map2/mapobject.h
SOURCES += layersmodel.cpp \
		   mapcanvas.cpp \
		   maplayer.cpp \
		   mapnavigation.cpp \
		   mapobject.cpp \
		   mapvectorobject.cpp \
		   mapview.cpp
