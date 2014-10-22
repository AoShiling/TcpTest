#-------------------------------------------------
#
# Project created by QtCreator 2014-10-22T17:10:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpCli
TEMPLATE = app


SOURCES += main.cpp\
		tcpcligui.cpp \
	tcpcli.cpp

HEADERS  += tcpcligui.h \
	tcpcli.h
