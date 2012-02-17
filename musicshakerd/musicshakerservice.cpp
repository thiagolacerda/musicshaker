#include "musicshakerservice.h"

MusicShakerService::MusicShakerService(QObject *parent) :
    QObject(parent),
    m_serviceEnabled(false),
    m_action(Next),
    m_sessionBus(QDBusConnection::sessionBus()),
    m_state(Unknown),
    m_settings("LacerdaApps", "musicshaker")
{
    qWarning() << "MusicShakerService CONSTRUCTOR";
    m_proxy = new MAFWProxy("com.nokia.mafw.renderer.MafwGstRendererPlugin.mafw_gst_renderer", "/com/nokia/mafw/renderer/mafw_gst_renderer",
                            m_sessionBus, this);
    m_reader = new AccelerometerReader(this);
    init();
}

MusicShakerService::~MusicShakerService()
{
    m_settings.setValue("action", m_action);
    m_settings.setValue("enabled", m_serviceEnabled);
    m_settings.sync();
}

void MusicShakerService::init()
{
    connect(m_reader, SIGNAL(shakeEvent()), this, SLOT(onShakeEvent()));
    getMediaPlayerState();
    m_sessionBus.connect("com.nokia.mafw.renderer.MafwGstRendererPlugin.mafw_gst_renderer",
                                           "/com/nokia/mafw/renderer/mafw_gst_renderer", MAFWProxy::staticInterfaceName(),
                                           "state_changed", this, SLOT(playbackStateChanged(int)));

    if (!m_settings.contains("action"))
        m_settings.setValue("action", MusicShakerService::Next);

    setAction((Action) m_settings.value("action").toInt(), false);

    if (!m_settings.contains("enabled"))
        m_settings.setValue("enabled", false);

    setServiceEnabled(m_settings.value("enabled").toBool(), false);
}

void MusicShakerService::getMediaPlayerState()
{
    QDBusMessage state = m_proxy->call("get_status");
    qWarning() << "MusicShakerService::getMediaPlayerState():" << state.type();
    if (state.type() != QDBusMessage::ReplyMessage)
        m_state = Unknown;
    else
        setMediaPlayerState(state.arguments().at(2).toInt());
}

bool MusicShakerService::serviceEnabled() const
{
    return m_serviceEnabled;
}

MusicShakerService::Action MusicShakerService::action() const
{
    return m_action;
}

void MusicShakerService::setServiceEnabled(bool serviceEnabled, bool sync)
{
    qWarning() << "MusicShakerService::setServiceEnabled():" << serviceEnabled;
    if (m_serviceEnabled != serviceEnabled) {
        m_serviceEnabled = serviceEnabled;
        if (m_serviceEnabled && m_state != Unknown)
            m_reader->startReading();
        else
            m_reader->stopReading();
        emit serviceEnabledChanged();

        if (sync)
            m_settings.setValue("enabled", m_serviceEnabled);
    }
}

void MusicShakerService::setAction(MusicShakerService::Action action, bool sync)
{
    qWarning() << "MusicShakerService::setAction():" << action;
    if (m_action != action) {
        m_action = action;

        if (sync)
            m_settings.setValue("action", m_action);
    }
}

void MusicShakerService::onShakeEvent()
{
    qWarning() << "onShakeEvent";
    switch(m_action) {
    case PlayPause: {
        if (m_state == Paused)
            m_proxy->resume();
        else if (m_state == Playing)
            m_proxy->pause();
        else
            m_proxy->play();
        break;
    }
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

void MusicShakerService::playbackStateChanged(int state)
{
    setMediaPlayerState(state);
}

void MusicShakerService::setMediaPlayerState(int state)
{
    if (state > 3) {
        m_state = Unknown;
        if (m_serviceEnabled && m_reader->isReading())
            m_reader->stopReading();
    } else {
        m_state = (MediaPlayerState) state;
        if (m_serviceEnabled && !m_reader->isReading())
            m_reader->startReading();
    }
    qWarning() << "MusicShakerService::setMediaPlayerState():"  << m_state;
}
