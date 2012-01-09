#ifndef MAFWPROXY
#define MAFWPROXY

#include <QtDBus/QtDBus>

class MAFWProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.nokia.mafw.renderer"; }

public:
    MAFWProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~MAFWProxy();

public slots:
    inline QDBusPendingReply<> next()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("next"), argumentList);
    }

    inline QDBusPendingReply<> pause()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("pause"), argumentList);
    }

    inline QDBusPendingReply<> play()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("play"), argumentList);
    }

    inline QDBusPendingReply<> previous()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("previous"), argumentList);
    }

    inline QDBusPendingReply<> resume()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("resume"), argumentList);
    }

    inline QDBusPendingReply<> stop()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("stop"), argumentList);
    }
};

#endif
