#ifndef ACCELEROMETERREADER_H
#define ACCELEROMETERREADER_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QTextStream>
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
    qreal m_lastAccel;
    qreal m_accelCurrent;
    qreal m_accel;
    quint32 m_minInterval;
    qtimestamp m_lastUpdateTime;
    QAccelerometer *m_accelerometer;
    QFile m_log;
    QTextStream m_inStream;
};

#endif // ACCELEROMETERREADER_H
