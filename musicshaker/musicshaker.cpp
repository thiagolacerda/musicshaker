#include "musicshaker.h"

MusicShaker::MusicShaker(QObject *parent) :
    QObject(parent)
{
    m_interface = new MusicShakerInterface("com.musicshaker.MSInterface", "/Adaptor", QDBusConnection::sessionBus());
    init();
}

void MusicShaker::init()
{
    qWarning() << "MusicShaker::init()";
    m_action = (Action) m_interface->action();
    m_enabled = m_interface->serviceEnabled();
}

void MusicShaker::setServiceEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        qWarning() << "valid:" << m_interface->isValid();
        m_interface->setServiceEnabled(m_enabled);
        emit serviceEnabledChanged();
    }
}

bool MusicShaker::serviceEnabled() const
{
    return m_enabled;
}

void MusicShaker::setAction(Action action)
{
    if (m_action != action) {
        qWarning() << "OPA " << action;
        m_action = action;
        m_interface->setAction((int) action);
        emit actionChanged();
    }
}

MusicShaker::Action MusicShaker::action() const
{
    return m_action;
}
