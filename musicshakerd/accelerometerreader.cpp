#include "accelerometerreader.h"
#include <QDebug>
#include <QDateTime>
#include <qmath.h>

AccelerometerReader::AccelerometerReader(QObject *parent) :
    QObject(parent),
    m_minInterval(1000000),
    m_lastUpdateTime(0),
    m_lastAccel(9.8),
    m_accelCurrent(9.8),
    m_accel(0)
{
    m_accelerometer = new QAccelerometer(this);
    m_accelerometer->addFilter(this);
    m_log.setFileName("/opt/musicshaker/musicshakerlog.txt");
}

AccelerometerReader::~AccelerometerReader()
{
    m_accelerometer->stop();
    m_accelerometer->deleteLater();
}

void AccelerometerReader::startReading()
{
    qWarning() << "start reading";
    if (m_log.exists())
        m_log.remove();
    m_log.open(QIODevice::WriteOnly);
    m_inStream.setDevice(&m_log);
    m_inStream << "started";
    m_inStream.flush();
    m_accelerometer->start();
}

void AccelerometerReader::stopReading()
{
    m_log.close();
    m_accelerometer->stop();
}

bool AccelerometerReader::filter(QAccelerometerReading *reading)
{
    qtimestamp timestamp = reading->timestamp();
    quint64 diffTime = timestamp - m_lastUpdateTime;
    //qWarning() << "enter filter " << timestamp << m_lastUpdateTime << diffTime;
    if (diffTime > m_minInterval) {
        //qWarning() << "inside";
        //Capture and process each accelerometer reading
        qreal x = reading->x();
        qreal y = reading->y();
        qreal z = reading->z();
        m_lastAccel = m_accelCurrent;

        m_accelCurrent = (qreal) qSqrt((qreal) (x*x + y*y + z*z));
        qreal delta = m_accelCurrent - m_lastAccel;
        m_accel = m_accel * 0.9 + delta;
        m_inStream << QDateTime::fromMSecsSinceEpoch(timestamp / 1000).toString("dd/MM/yyyy hh:mm:ss") << "\n";
        m_inStream << "x: " << x << ", y: " << y << ", z: " << z << "\n";
        m_inStream << "m_accelCurrent: " << m_accelCurrent << ", delta: " << delta << ", m_accel: " << m_accel << "\n";
        if (m_accel > 5) {
            qWarning() << "SHAKEEE!!!!";
            m_inStream << "SHAKE\n";
            m_lastUpdateTime = timestamp;
            emit shakeEvent();
        }
        m_inStream.flush();
    }

    return true;
}
