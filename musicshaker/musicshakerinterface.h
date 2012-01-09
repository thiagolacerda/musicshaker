#ifndef MUSICSHAKERINTERFACE_H
#define MUSICSHAKERINTERFACE_H

#include <QtDBus/QtDBus>

class MusicShakerInterface : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.musicshaker.MSInterface"; }

    MusicShakerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    void setService(bool enabled) {
        qWarning() << "CALLED: " << enabled;
        setServiceEnabled(enabled);
    }

public slots:
    inline QDBusPendingReply<> setServiceEnabled(bool enabled)
    {
        qWarning() << "CALLED2: " << enabled;
        return asyncCall(QLatin1String("setServiceEnabled"), enabled);
    }
};

#endif // MUSICSHAKERINTERFACE_H
