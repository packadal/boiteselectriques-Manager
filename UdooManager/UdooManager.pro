#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T10:58:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UdooManager
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
		MainWindow.cpp \
	MainWidget.cpp \
	ChannelEditor.cpp \
	SaveManager.cpp

HEADERS  += MainWindow.h \
	MainWidget.h \
	ChannelEditor.h \
	SaveManager.h

FORMS    += MainWindow.ui \
	MainWidget.ui \
	ChannelEditor.ui

INCLUDEPATH += /usr/local/include/KF5/KArchive
LIBS += -lKF5Archive
