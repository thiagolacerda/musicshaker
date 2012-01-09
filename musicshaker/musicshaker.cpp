#include "musicshaker.h"

MusicShaker::MusicShaker(QObject *parent) :
    QObject(parent)
{
    m_interface = new MusicShakerInterface("com.musicshaker.MSInterface", "/Adaptor", QDBusConnection::sessionBus());
}

void MusicShaker::setServiceEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        qWarning() << "valid:" << m_interface->isValid();
        m_interface->setService(m_enabled);
        emit serviceEnabledChanged();
    }
}

bool MusicShaker::serviceEnabled() const
{
    return m_enabled;
}
