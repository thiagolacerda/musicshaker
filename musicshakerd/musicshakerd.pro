#-------------------------------------------------
#
# Project created by QtCreator 2012-01-07T18:37:17
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = musicshakerd
CONFIG   += console
CONFIG += debug
CONFIG   -= app_bundle
CONFIG += mobility

MOBILITY += sensors

TEMPLATE = app

musicshakerd.path = /etc/init/apps
musicshakerd.files = musicshakerd.conf

INSTALLS += musicshakerd


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
    target.path = /opt/musicshaker/bin
    INSTALLS += target
}
