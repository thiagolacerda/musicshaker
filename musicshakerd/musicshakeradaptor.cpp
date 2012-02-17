#include "musicshakeradaptor.h"
#include "musicshakerservice.h"
#include <QDebug>

MusicShakerAdaptor::MusicShakerAdaptor(MusicShakerService *service)
    : QDBusAbstractAdaptor(service),
      m_service(service)
{
}

MusicShakerAdaptor::~MusicShakerAdaptor()
{
}

void MusicShakerAdaptor::setServiceEnabled(bool enabled)
{
    qWarning() << "setServiceEnabled() on adaptor:" << enabled;
    m_service->setServiceEnabled(enabled);
}

void MusicShakerAdaptor::setAction(int action)
{
    qWarning() << "setAction() on adaptor:" << action;
    m_service->setAction((MusicShakerService::Action) action);
}

bool MusicShakerAdaptor::serviceEnabled()
{
    qWarning() << "ADAPTOR serviceEnabled()" << m_service->serviceEnabled();
    return m_service->serviceEnabled();
}

int MusicShakerAdaptor::action()
{
    qWarning() << "ADAPTOR action()" << m_service->action();
    return m_service->action();
}
