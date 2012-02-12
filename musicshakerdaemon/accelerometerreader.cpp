#include "accelerometerreader.h"
#include <QDebug>
#include <qmath.h>

AccelerometerReader::AccelerometerReader(QObject *parent) :
    QObject(parent),
    m_threshold(800),
    m_minInterval(100000)
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
}

void AccelerometerReader::stopReading()
{
    m_accelerometer->stop();
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

        qreal speed = qAbs((x + y + z) - (m_lastX + m_lastY + m_lastZ)) / diffTime * 10000;
        if (speed > m_threshold)
            emit shakeEvent();

        m_lastX = x;
        m_lastY = y;
        m_lastZ = z;
    }

    return true;
}
