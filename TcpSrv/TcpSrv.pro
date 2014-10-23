#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T08:12:23
#
#-------------------------------------------------

QT       += core gui network

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpSrv
TEMPLATE = app


SOURCES += main.cpp\
		tcpsrvgui.cpp \
	tcpsrv.cpp

HEADERS  += tcpsrvgui.h \
	tcpsrv.h
