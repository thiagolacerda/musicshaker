#ifndef MUSICSHAKER_H
#define MUSICSHAKER_H

#include <QObject>
#include "musicshakerinterface.h"

class MusicShaker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool serviceEnabled READ serviceEnabled WRITE setServiceEnabled NOTIFY serviceEnabledChanged)
    Q_PROPERTY(Action action READ action WRITE setAction NOTIFY actionChanged)
    Q_ENUMS(Action)

public:
    explicit MusicShaker(QObject *parent = 0);

    enum Action {
        PlayPause,
        Next,
        Previous
    };

    void setServiceEnabled(bool enabled);
    bool serviceEnabled() const;

    void setAction(Action action);
    Action action() const;

signals:
    void serviceEnabledChanged();
    void actionChanged();
    
private:
    void init();
    MusicShakerInterface *m_interface;
    bool m_enabled;
    Action m_action;
};

#endif // MUSICSHAKER_H
