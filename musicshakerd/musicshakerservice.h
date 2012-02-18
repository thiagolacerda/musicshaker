#ifndef MUSICSHAKERSERVICE_H
#define MUSICSHAKERSERVICE_H

#include <QObject>
#include "accelerometerreader.h"
#include "mafwproxy.h"

QTM_USE_NAMESPACE

class MusicShakerService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool serviceEnabled READ serviceEnabled NOTIFY serviceEnabledChanged)

public:
    MusicShakerService(QObject *parent = 0);
    ~MusicShakerService();

    enum Action {
        PlayPause,
        Next,
        Previous
    };

    enum MediaPlayerState {
        Stopped,
        Playing,
        Paused,
        Transitioning,
        Unknown
    };

    bool serviceEnabled() const;

    Action action() const;

signals:
    void serviceEnabledChanged();

public slots:
    void setServiceEnabled(bool enabled, bool sync = true);
    void setAction(MusicShakerService::Action action, bool sync = true);

private slots:
    void onShakeEvent();
    void playbackStateChanged(int state);

private:
    void init();
    void getMediaPlayerState();
    void setMediaPlayerState(int state);
    bool m_serviceEnabled;
    AccelerometerReader *m_reader;
    MAFWProxy *m_proxy;
    Action m_action;
    QDBusConnection m_sessionBus;
    MediaPlayerState m_state;
};

#endif // MUSICSHAKERSERVICE_H
