#include "musicshakeradaptor.h"
#include "musicshakerservice.h"
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

void MusicShakerAdaptor::setAction(int action)
{
    qWarning() << "SET ACTION" << action;
    QMetaObject::invokeMethod(parent(), "setAction", Q_ARG(MusicShakerService::Action, (MusicShakerService::Action) action));
}
