#include <QtCore/QCoreApplication>
#include "musicshakerservice.h"
#include "musicshakeradaptor.h"
#include <QtDBus/QtDBus>
#include <QDebug>

QTM_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qWarning() << "FOI";
    MusicShakerService *service = new MusicShakerService();
    new MusicShakerAdaptor(service);
    qWarning() << "opa " << service;
    QDBusConnection connection = QDBusConnection::sessionBus();
    qWarning() << "connection: ";
    qWarning() << connection.registerObject("/Adaptor", service);
    qWarning() << "aaa";
    qWarning() << connection.registerService("com.musicshaker.MSInterface");
    qWarning() << "bbb";
    return a.exec();
}
