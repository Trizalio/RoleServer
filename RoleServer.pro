#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T23:16:08
#
#-------------------------------------------------
QT       += core
QT       += network
QT       += websockets
#QT       += sql

CONFIG += c++11

QT       -= gui

TARGET = RoleServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    echoserver.cpp \
    console.cpp \
    orm/csqlconnector.cpp \
    cplanetmap.cpp \
    ccell.cpp \
    cplanetthread.cpp \
    cplanetjson.cpp \
    orm/corm.cpp

HEADERS += \
    echoserver.h \
    console.h \
    orm/csqlconnector.h \
    cplanetmap.h \
    ccell.h \
    cplanetthread.h \
    cplanetjson.h \
    orm/sql_objects/suser.h \
    orm/corm.h

unix:!macx: LIBS += -L$$PWD/../../sdk/mysql-connector/lib/ -lmysqlcppconn

INCLUDEPATH += $$PWD/../../sdk/mysql-connector/include
DEPENDPATH += $$PWD/../../sdk/mysql-connector/include
