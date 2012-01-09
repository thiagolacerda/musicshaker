#include "accelerometerreader.h"
#include <QDebug>
#include <qmath.h>

AccelerometerReader::AccelerometerReader(QObject *parent) :
    QObject(parent),
    m_SDAccelThreshold(5.0),
    m_minInterval(2.0),
    m_lastShakeEventTime(0)
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

void AccelerometerReader::clearValues()
{
    xValues.clear();
    yValues.clear();
    zValues.clear();
}

bool AccelerometerReader::filter(QAccelerometerReading *reading)
{
    //Capture and process each accelerometer reading

    qreal x = reading->x();
    qreal y = reading->y();
    qreal z = reading->z();

    qtimestamp timestamp = reading->timestamp();

    //qWarning() << "CHANGED: " << x << ", " << y << ", " << z << ", timestamp: " << timestamp;

    qreal xAccelStandardDeviation =  0;
    qreal yAccelStandardDeviation =  0;
    qreal zAccelStandardDeviation =  0;

    //We store past 20 accel. readings for each direction.

    //If the queue reaches 20, dequeue/remove the oldest reading
    if (xValues.length() >= 20) {
        xValues.takeFirst();
        yValues.takeFirst();
        zValues.takeFirst();

        //Now add the current reading to the list (at last position - which is taken care by the awesome QQueue class)
        xValues.append(x);
        yValues.append(y);
        zValues.append(z);

        //Calculate standard deviation in each direction for the last 20 readings
        xAccelStandardDeviation = standardDeviation(xValues);
        yAccelStandardDeviation = standardDeviation(yValues);
        zAccelStandardDeviation = standardDeviation(zValues);
        qWarning() << "calculate all sd";
    } else {
        /* We don't have sufficient (20) readings to determine which direction the phone is moving.
           So, keep adding the readings to the queue.
         */
        xValues.append(x);
        yValues.append(y);
        zValues.append(z);
    }
    /*Now for the interesting part.

      If the standard deviation in x axis is more than the set threshold and also more than double the SD in y and z axes, we identify the phone is being shaken horizontally.
      This avoids accidental triggers due to walking etc. In harmattan sensors readings are not available when the display is off,
      which means this function will not be called when display is off (screen locked). This also reduces the possibility of accidental triggers.
     */

    if (xAccelStandardDeviation > m_SDAccelThreshold
            && xAccelStandardDeviation > (yAccelStandardDeviation * 2)
            && xAccelStandardDeviation > (zAccelStandardDeviation * 2)) {

        //qDebug() << "Time since last detection (secs): "<<(reading->timestamp() - lastDetectionTimestamp)/qPow(10,6);
        if ((timestamp - m_lastShakeEventTime)/qPow(10,6) > m_minInterval) {

            emit shakeEvent();

            m_lastShakeEventTime = timestamp;
            qWarning() << "detectou!!!!!!!!!!";
        } else{
            qWarning() << "Shake recognized but "
                     <<  (m_minInterval - ((timestamp - m_lastShakeEventTime)/qPow(10,6)))
                     << " more seconds remain until next trigger";
        }
        qDebug()<< "Clearing last " << xValues.length() << " readings";
        clearValues();
    }

    return true;
}

qreal AccelerometerReader::mean(const QList<qreal> &values) const
{
 // Calculate average acceleration from the range of (20) values
    qreal sum = 0;
    qreal mean = 0;
    int listSize = values.size();

    foreach (qreal value, values)
        sum += value;

    if (listSize != 0) mean = sum/((qreal) listSize);
    return mean;
}

qreal AccelerometerReader::standardDeviation(const QList<qreal> &values) const
{
    // Calculate Standard Deviation from the range of (20) accelerometer readings

    qreal diffSquareSum = 0;
    qreal standardDeviation = 0;
    qreal meanValue = mean(values);
    int listSize = values.size();

    foreach (qreal value, values)
        diffSquareSum += qPow(value - meanValue,2);

    if (listSize != 0)
        standardDeviation = qSqrt(diffSquareSum/((qreal) listSize));
    return standardDeviation;
}
