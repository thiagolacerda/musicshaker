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

//public slots:

private:
    qreal mean(const QList<qreal> &values) const;
    qreal standardDeviation(const QList<qreal> &values) const;
    void clearValues();

    QList<qreal> xValues;
    QList<qreal> yValues;
    QList<qreal> zValues;

    qreal m_SDAccelThreshold;
    qreal m_minInterval;
    qtimestamp m_lastShakeEventTime;
    QAccelerometer *m_accelerometer;
};

#endif // ACCELEROMETERREADER_H
