#ifndef MUSICSHAKER_H
#define MUSICSHAKER_H

#include <QObject>
#include "musicshakerinterface.h"

class MusicShaker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool serviceEnabled READ serviceEnabled WRITE setServiceEnabled NOTIFY serviceEnabledChanged)

public:
    explicit MusicShaker(QObject *parent = 0);

    void setServiceEnabled(bool enabled);
    bool serviceEnabled() const;

signals:
    void serviceEnabledChanged();
    
private:
    MusicShakerInterface *m_interface;
    bool m_enabled;
};

#endif // MUSICSHAKER_H
