#ifndef ACCELEROMETERREADER_H
#define ACCELEROMETERREADER_H

#include <QObject>
#include <QList>
//#include <qaccele>
#include <qaccelerometer.h>

QTM_USE_NAMESPACE

class AccelerometerReader : public QObject, public QAccelerometerFilter
{
    Q_OBJECT
public:
    explicit AccelerometerReader(QObject *parent = 0);
    ~AccelerometerReader();

    bool filter(QAccelerometerReading *reading);

    void startReading();
    void stopReading();
    
signals:
    void shakeEvent();

private:
    qreal m_threshold;
    quint32 m_minInterval;
    qtimestamp m_lastUpdateTime;
    QAccelerometer *m_accelerometer;
    qreal m_lastX;
    qreal m_lastY;
    qreal m_lastZ;
};

#endif // ACCELEROMETERREADER_H
