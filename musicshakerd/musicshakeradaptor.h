#ifndef MUSICSHAKERADAPTOR_H
#define MUSICSHAKERADAPTOR_H

#include <QtDBus/QtDBus>

class MusicShakerAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.musicshaker.MSInterface")

public:
    MusicShakerAdaptor(QObject *parent = 0);
    virtual ~MusicShakerAdaptor();

public slots:
    void setServiceEnabled(bool enabled);
    void setAction(int action);

signals:
    void enableDisableService(bool enabled);
};

#endif // MUSICSHAKERADAPTOR_H
