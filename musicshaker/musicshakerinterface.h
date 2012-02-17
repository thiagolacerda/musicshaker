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

    /*void setService(bool enabled) {
        qWarning() << "CALLED: " << enabled;
        setServiceEnabled(enabled);
    }*/

public slots:
    inline QDBusPendingReply<> setServiceEnabled(bool enabled)
    {
        qWarning() << "CALLED2: " << enabled;
        return asyncCall(QLatin1String("setServiceEnabled"), enabled);
    }

    inline QDBusPendingReply<> setAction(int action)
    {
        qWarning() << "CALLED action: " << action;
        return asyncCall(QLatin1String("setAction"), action);
    }

    inline int action()
    {
        QDBusMessage message = call("action");
        QDBusReply<int> a = call("action");
        qWarning() << "called action on UI" << a;
        qWarning() << "called action on UI message" << message;
        return a;
    }

    inline bool serviceEnabled()
    {
        QDBusMessage message = call("serviceEnabled");
        QDBusReply<bool> a = call("serviceEnabled");
        qWarning() << "called serviceEnabled on UI" << a;
        qWarning() << "called serviceEnabled on UI message" << message;
        return a;
    }
};

#endif // MUSICSHAKERINTERFACE_H
