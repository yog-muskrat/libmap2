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

QT += gui
greaterThan(QT_MAJOR_VERSION, 4)
{
  QT += widgets
}

QMAKE_CXXFLAGS += -isystem $$PWD/../include/gis

LIBS += -L../lib/gis -l mapacces

HEADERS += mapcanvas.h \
	mapnavigation.h \
	../include/map2/layersmodel.h \
	../include/map2/maplayer.h \
	../include/map2/mapvectorobject.h \
	../include/map2/mapview.h \
	../include/map2/structs.h \
	../include/map2/mapobject.h \
	../include/map2/rscselectdialog.h \
	../include/map2/rscviewer.h \
	../include/map2/maptools.h \
	../include/map2/gis.h \
    ../include/map2/maplineobject.h \
    ../include/map2/mapzoneobject.h
SOURCES += layersmodel.cpp \
		   mapcanvas.cpp \
		   maplayer.cpp \
		   mapnavigation.cpp \
		   mapobject.cpp \
		   mapvectorobject.cpp \
		   mapview.cpp \
	rscselectdialog.cpp \
	rscviewer.cpp \
	maptools.cpp \
	structs.cpp \
    maplineobject.cpp \
    mapzoneobject.cpp

FORMS += \
	rscselectdialog.ui \
	rscviewer.ui
