#-------------------------------------------------
#
# Project created by QtCreator 2025-07-24T20:25:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = h_client
TEMPLATE = app


SOURCES += main.cpp\
        client_h.cpp

HEADERS  += client_h.h \
    struct.h

FORMS    += client_h.ui

CONFIG += C++11
