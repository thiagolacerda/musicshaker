#-------------------------------------------------
#
# Project created by QtCreator 2012-01-07T18:37:17
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = musicshakerdaemon
CONFIG   += console
CONFIG += debug
CONFIG   -= app_bundle
CONFIG += mobility

MOBILITY += sensors

TEMPLATE = app

musicshakerdaemon.path = /etc/init/apps
musicshakerdaemon.files = musicshakerdaemon.conf

INSTALLS += musicshakerdaemon


SOURCES += main.cpp \
    musicshakeradaptor.cpp \
    mafwproxy.cpp \
    accelerometerreader.cpp \
    musicshakerservice.cpp

HEADERS += \
    musicshakeradaptor.h \
    mafwproxy.h \
    accelerometerreader.h \
    musicshakerservice.h

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/musicshakerdaemon/bin
    INSTALLS += target
}
