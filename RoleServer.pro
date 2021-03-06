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
CONFIG  += c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server/echoserver.cpp \
    console.cpp \
    orm/csqlconnector.cpp \
    cplanetmap.cpp \
    ccell.cpp \
    cplanetthread.cpp \
    cplanetjson.cpp \
    orm/corm.cpp \
    server/cserverlogic.cpp \
    orm/aggregation_objects/cuser.cpp \
    orm/aggregation_objects/cgroup.cpp \
    orm/sql_objects/sgroup.cpp \
    orm/sql_objects/suser.cpp \
    orm/sql_objects/cjsonserializable.cpp \
    orm/sql_objects/snews.cpp \
    orm/aggregation_objects/cnews.cpp \
    orm/aggregation_objects/cplayer.cpp \
    orm/sql_objects/scredential.cpp \
    orm/sql_objects/splayer.cpp \
    cconnectionkeeper.cpp \
    orm/sql_objects/suserstat.cpp \
    orm/sql_objects/sitem.cpp \
    items/shealshot.cpp \
    items/iitem.cpp \
    common/common.cpp \
    items/citemmanager.cpp \
    items/sairlock.cpp \
    tick/ctickmanager.cpp \
    items/saircell.cpp \
    orm/sql_objects/slore.cpp

HEADERS += \
    server/echoserver.h \
    console.h \
    orm/csqlconnector.h \
    cplanetmap.h \
    ccell.h \
    cplanetthread.h \
    cplanetjson.h \
    orm/sql_objects/suser.h \
    orm/corm.h \
    orm/sql_objects/splayer.h \
    orm/sql_objects/scredential.h \
    orm/sql_objects/smessage.h \
    server/cserverlogic.h \
    #orm/sql_objects/sdialogue.h \
    orm/aggregation_objects/sdialogue.h \
    orm/sql_objects/sgroup.h \
    orm/sql_objects/srole.h \
    orm/aggregation_objects/cuser.h \
    orm/aggregation_objects/cgroup.h \
    orm/sql_objects/cjsonserializable.h \
    orm/sql_objects/snews.h \
    orm/aggregation_objects/cnews.h \
    orm/aggregation_objects/cplayer.h \
    cconnectionkeeper.h \
    orm/sql_objects/suserstat.h \
    orm/sql_objects/sitem.h \
    items/shealshot.h \
    items/iitem.h \
    common/common.h \
    items/citemmanager.h \
    items/sairlock.h \
    tick/ctickmanager.h \
    items/saircell.h \
    orm/sql_objects/slore.h

unix:!macx: LIBS += -L$$PWD/../../sdk/mysql-connector/lib/ -lmysqlcppconn

INCLUDEPATH += $$PWD/../../sdk/mysql-connector/include
DEPENDPATH += $$PWD/../../sdk/mysql-connector/include
