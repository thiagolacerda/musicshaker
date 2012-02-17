#ifndef ACCELEROMETERREADER_H
#define ACCELEROMETERREADER_H

#include <QObject>
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

    bool isReading() const;

signals:
    void shakeEvent();

private:
    qreal m_lastAccel;
    qreal m_accelCurrent;
    qreal m_accel;
    quint64 m_minInterval;
    qtimestamp m_lastUpdateTime;
    QAccelerometer *m_accelerometer;
    bool m_reading;
};

#endif // ACCELEROMETERREADER_H
