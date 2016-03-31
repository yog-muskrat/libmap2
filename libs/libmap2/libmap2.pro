include (../../common.pri)

GISLIBPATH = $${libs_path}/gis
GISINCLUDEPATH = gis/include

contains(DEFINES, MSVS_5){
	GISLIBPATH = /usr/local/GISCore/lib
	GISINCLUDEPATH = /usr/local/GISCore/include
	message("Using GIS libs in /usr/local/GISCore")
}

TEMPLATE = lib
TARGET = map2
DESTDIR = ../../lib
INCLUDEPATH += \
			../../include \
			../../include/map2 \
			$$GISINCLUDEPATH

QT += gui

greaterThan(QT_MAJOR_VERSION, 4){
  QT += widgets
}

LIBS += -L$$GISLIBPATH -lmapacces

HEADERS += \
	../../include/map2/rscselectdialog.h \
	../../include/map2/layersmodel.h \
	../../include/map2/rscviewer.h \
	../../include/map2/maphelper.h \
	../../include/map2/maplayer.h \
	../../include/map2/mapstructs.h \
	../../include/map2/mapview.h \
	gis.h \
	mapcanvas.h \
	actions/mapaction.h \
	actions/mapmoveaction.h \
	actions/mapdeleteaction.h \
	actions/maprotateaction.h \
	actions/maprectzoomaction.h \
	actions/mapruleraction.h \
	actions/mapvectorobjectaction.h \
	actions/maplineobjectaction.h \
	actions/mapzoneobjectaction.h \
	actions/mapnoaction.h \
	../../include/map2/mapeditor.h \
	../../include/map2/widgets/layerswidget.h \
	../../include/map2/widgets/objectswidget.h \
	../../include/map2/widgets/maptoolbar.h \
	../../include/map2/widgets/mapnavigation.h \
	../../include/map2/widgets/mapinfowidget.h \
	../../include/map2/objects/maplineobject.h \
	../../include/map2/objects/mapobject.h \
	../../include/map2/objects/maptextobject.h \
	../../include/map2/objects/mapvectorobject.h \
	../../include/map2/objects/mapzoneobject.h \
	mapruler.h \
	../../include/map2/groups/mapgroup.h \
	../../include/map2/groups/mapstackgroup.h \
	../../include/map2/mapgroupsmodel.h \
	../../include/map2/groups/mapformulargroup.h \
	../../include/map2/widgets/layerssettingsdialog.h \
	../../include/map2/widgets/calibrationdialog.h \
	../../include/map2/objects/mapcommlineobject.h \
	../../include/map2/objects/mapsectorobject.h \
    ../../include/map2/widgets/coordedit.h

SOURCES +=\
			rscselectdialog.cpp \
			layersmodel.cpp \
			mapstructs.cpp \
			maphelper.cpp \
			rscviewer.cpp \
			mapcanvas.cpp \
			maplayer.cpp \
			mapview.cpp \
	actions/mapmoveaction.cpp \
	actions/mapdeleteaction.cpp \
	actions/maprotateaction.cpp \
	actions/maprectzoomaction.cpp \
	actions/mapruleraction.cpp \
	actions/mapvectorobjectaction.cpp \
	actions/maplineobjectaction.cpp \
	actions/mapzoneobjectaction.cpp \
	actions/mapnoaction.cpp \
	mapeditor.cpp \
	widgets/layerswidget.cpp \
	widgets/objectswidget.cpp \
	widgets/maptoolbar.cpp \
	widgets/mapnavigation.cpp \
	widgets/mapinfowidget.cpp \
	objects/maplineobject.cpp \
	objects/mapobject.cpp \
	objects/maptextobject.cpp \
	objects/mapvectorobject.cpp \
	objects/mapzoneobject.cpp \
	mapruler.cpp \
	groups/mapstackgroup.cpp \
	mapgroupsmodel.cpp \
	groups/mapformulargroup.cpp \
	groups/mapgroup.cpp \
	widgets/layerssettingsdialog.cpp \
	widgets/calibrationdialog.cpp \
	objects/mapcommlineobject.cpp \
	objects/mapsectorobject.cpp \
    widgets/coordedit.cpp

FORMS += \
	rscselectdialog.ui \
	rscviewer.ui \
	widgets/layerssettingsdialog.ui \
	widgets/calibrationdialog.ui

RESOURCES += \
	map2res.qrc
