#include <QtCore/QCoreApplication>
#include "musicshakerservice.h"
#include "musicshakeradaptor.h"
#include <QtDBus/QtDBus>
#include <QDebug>

QTM_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MusicShakerService *service = new MusicShakerService();
    new MusicShakerAdaptor(service);
    qWarning() << "opa " << service;
    QDBusConnection connection = QDBusConnection::sessionBus();
    qWarning() << "connection";
    qWarning() << "registerObject" << connection.registerObject("/Adaptor", service);
    qWarning() << "registerService" << connection.registerService("com.musicshaker.MSInterface");
    return a.exec();
}
