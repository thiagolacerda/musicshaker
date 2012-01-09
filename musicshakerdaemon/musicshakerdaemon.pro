#-------------------------------------------------
#
# Project created by QtCreator 2012-01-07T18:37:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = musicshakerdaemon
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += qdbus
CONFIG += mobility

MOBILITY += sensors

TEMPLATE = app

daemon.path = /etc/init/apps
daemon.files = msdaemon.conf

INSTALLS += daemon


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
