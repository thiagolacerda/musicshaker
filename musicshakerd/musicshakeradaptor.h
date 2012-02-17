#ifndef MUSICSHAKERADAPTOR_H
#define MUSICSHAKERADAPTOR_H

#include <QtDBus/QtDBus>
#include "musicshakerservice.h"

class MusicShakerAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.musicshaker.MSInterface")

public:
    MusicShakerAdaptor(MusicShakerService *service);
    virtual ~MusicShakerAdaptor();

public slots:
    void setServiceEnabled(bool enabled);
    void setAction(int action);

    bool serviceEnabled();
    int action();

signals:
    void enableDisableService(bool enabled);

private:
    MusicShakerService *m_service;
};

#endif // MUSICSHAKERADAPTOR_H
