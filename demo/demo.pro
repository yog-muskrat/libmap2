include (../common.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += ../include

LIBS += -L../lib -lmap2

SOURCES += main.cpp\
		mainwindow.cpp

HEADERS  += mainwindow.h
