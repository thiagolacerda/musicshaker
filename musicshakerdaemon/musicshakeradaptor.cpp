#include "musicshakeradaptor.h"
#include <QDebug>

MusicShakerAdaptor::MusicShakerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
}

MusicShakerAdaptor::~MusicShakerAdaptor()
{
}

void MusicShakerAdaptor::setServiceEnabled(bool enabled)
{
    if (enabled)
        qWarning() << "ENABLED";
    else
        qWarning() << "DISABLED";
    QMetaObject::invokeMethod(parent(), "setServiceEnabled", Q_ARG(bool, enabled));
}

