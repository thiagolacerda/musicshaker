#ifndef MUSICSHAKERSERVICE_H
#define MUSICSHAKERSERVICE_H

#include <QObject>
#include "accelerometerreader.h"
#include "musicshakeradaptor.h"
#include "mafwproxy.h"

QTM_USE_NAMESPACE

class MusicShakerService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool serviceEnabled READ serviceEnabled NOTIFY serviceEnabledChanged)

public:
    MusicShakerService(QObject *parent = 0);

    bool serviceEnabled() const;

signals:
    void serviceEnabledChanged();

private slots:
    void setServiceEnabled(bool enabled);
    void onShakeEvent();

private:
    bool m_serviceEnabled;
    AccelerometerReader *m_reader;
    MAFWProxy *m_proxy;
    //MusicShakerAdaptor *m_adaptor;
};

#endif // MUSICSHAKERSERVICE_H
