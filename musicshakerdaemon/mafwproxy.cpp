#include "mafwproxy.h"

MAFWProxy::MAFWProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

MAFWProxy::~MAFWProxy()
{
}

