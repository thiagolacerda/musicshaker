#include "accelerometerreader.h"
#include <QDebug>
#include <QDateTime>
#include <qmath.h>

AccelerometerReader::AccelerometerReader(QObject *parent) :
    QObject(parent),
    m_lastAccel(9.8),
    m_accelCurrent(9.8),
    m_accel(0),
    m_minInterval(1000000),
    m_lastUpdateTime(0),
    m_reading(false)
{
    m_accelerometer = new QAccelerometer(this);
    m_accelerometer->addFilter(this);
}

AccelerometerReader::~AccelerometerReader()
{
    m_accelerometer->stop();
    m_accelerometer->deleteLater();
}

void AccelerometerReader::startReading()
{
    qWarning() << "start reading";
    m_accelerometer->start();
    m_reading = true;
}

void AccelerometerReader::stopReading()
{
    m_accelerometer->stop();
    m_reading = false;
}

bool AccelerometerReader::filter(QAccelerometerReading *reading)
{
    qtimestamp timestamp = reading->timestamp();
    quint64 diffTime = timestamp - m_lastUpdateTime;
    if (diffTime > m_minInterval) {
        //Capture and process each accelerometer reading
        qreal x = reading->x();
        qreal y = reading->y();
        qreal z = reading->z();
        m_lastAccel = m_accelCurrent;

        m_accelCurrent = (qreal) qSqrt((qreal) (x*x + y*y + z*z));
        qreal delta = m_accelCurrent - m_lastAccel;
        m_accel = m_accel * 0.9 + delta;
        qWarning() << QDateTime::fromMSecsSinceEpoch(timestamp / 1000).toString("dd/MM/yyyy hh:mm:ss") << "\n";
        qWarning() << "x: " << x << ", y: " << y << ", z: " << z << "\n";
        qWarning() << "m_accelCurrent: " << m_accelCurrent << ", delta: " << delta << ", m_accel: " << m_accel << "\n";
        if (m_accel > 11) {
            qWarning() << "SHAKEEE!!!!";
            m_lastUpdateTime = timestamp;
            emit shakeEvent();
        }
    }
    return true;
}

bool AccelerometerReader::isReading() const
{
    return m_reading;
}
