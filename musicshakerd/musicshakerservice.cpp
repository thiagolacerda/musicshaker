#include "musicshakerservice.h"

MusicShakerService::MusicShakerService(QObject *parent) :
    QObject(parent),
    m_serviceEnabled(false)
{
    qWarning() << "CONSTRUCTOR";
    //m_adaptor = new MusicShakerAdaptor(this);
    m_proxy = new MAFWProxy("com.nokia.mafw.renderer.MafwGstRendererPlugin.mafw_gst_renderer", "/com/nokia/mafw/renderer/mafw_gst_renderer",
                            QDBusConnection::sessionBus(), this);
    m_reader = new AccelerometerReader(this);
    connect(m_reader, SIGNAL(shakeEvent()), this, SLOT(onShakeEvent()));
    m_action = Next;
    /*QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/Adaptor", m_adaptor);
    connection.registerService("com.musicshaker.MSInterface");
    connect(m_adaptor, SIGNAL(enableDisableService(bool)), this, SLOT(setServiceEnabled(bool)));*/
}

bool MusicShakerService::serviceEnabled() const
{
    return m_serviceEnabled;
}

void MusicShakerService::setServiceEnabled(bool serviceEnabled)
{
    qWarning() << "set enabled: " << serviceEnabled;
    if (m_serviceEnabled != serviceEnabled) {
        m_serviceEnabled = serviceEnabled;
        if (m_serviceEnabled)
            m_reader->startReading();
        else
            m_reader->stopReading();
        emit serviceEnabledChanged();
    }
}

void MusicShakerService::setAction(MusicShakerService::Action action)
{
    qWarning() << "ON PARENT" << action;
    m_action = action;
}

void MusicShakerService::onShakeEvent()
{
    qWarning() << "onShakeEvent";
    switch(m_action) {
    case PlayPause:
        //m_proxy->
        break;
    case Next: {
        qWarning() << "will change song" << m_proxy->isValid();
        m_proxy->next();
        break;
    }
    case Previous: {
        qWarning() << "will change song previous" << m_proxy->isValid();
        m_proxy->previous();
        break;
    }
    }
}
