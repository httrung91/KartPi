#include "kartrpi_kartstatusmodel.h"

KartRpi_KartStatusModel &KartRpi_KartStatusModel::Instance()
{
    static KartRpi_KartStatusModel instance;
    return instance;
}

void KartRpi_KartStatusModel::init()
{
    setSpeedLimit(35);
    setRacingTime("--:--");
    setIsUnderShieldEffect(false);
    setIsUnderSpeedEffect(false);
    setIsUnderBombEffect(false);
    setIsUsingLaserGun(false);
    setRacingTimeMilliS(0);

    m_racingTimer = new QTimer(this);
    m_racingTimer->setInterval(1000);
    connect(m_racingTimer, SIGNAL(timeout()), this, SLOT(updateTimeLap()));
}

void KartRpi_KartStatusModel::startTimeLapCounter()
{
    setRacingTime("00:00");
    m_racingTimer->start();
}

void KartRpi_KartStatusModel::stopTimeLapCounter()
{
    m_racingTimer->stop();
    setRacingTimeMilliS(0);
}

void KartRpi_KartStatusModel::decreaseTimeLap()
{
    qDebug() << "Decrease Racing Time";
    KARTRPI_CONSOLE.appendConsoleData("Decrease Racing Time");
    quint64 temp = racingTimeMilliS();
    if(temp < 15){
        temp = 0;
    }
    else{
        temp = temp - 15;
    }
    setRacingTimeMilliS(temp);

    quint8 hours = racingTimeMilliS() / 3600;
    quint8 minutes = (racingTimeMilliS() - hours*3600) / 60;
    quint8 seconds = (racingTimeMilliS() - hours*3600 - minutes*60);

    QString strHours = "";
    QString strMinutes = "";
    QString strSeconds = "";

    if(hours < 10){
        strHours = "0" + QString::number(hours);
    }
    else{
        strHours = QString::number(hours);
    }
    if(minutes < 10){
        strMinutes = "0" + QString::number(minutes);
    }
    else{
        strMinutes = QString::number(minutes);
    }
    if(seconds < 10){
        strSeconds = "0" + QString::number(seconds);
    }
    else{
        strSeconds = QString::number(seconds);
    }

//    QString timeString =  + ":" + QString::number(minutes) + ":" + QString::number(seconds);
    qDebug() << strHours + ":" + strMinutes + ":" + strSeconds;
    setRacingTime(strMinutes + ":" + strSeconds);

}

void KartRpi_KartStatusModel::hitByLaser()
{
    if(m_isUnderShieldEffect){
        qDebug() << "Shield is ON - No Effect";
        KARTRPI_CONSOLE.appendConsoleData("Shield is ON - No Effect");
        return;
    }

    qDebug() << "Kart is hit by Laser";
    KARTRPI_CONSOLE.appendConsoleData("Kart is hit by Laser");
    setSpeedLimit(20);
}

void KartRpi_KartStatusModel::updateTimeLap()
{
    qDebug() << "Update Racing Time...";
    quint64 temp = racingTimeMilliS();
    temp++;
    setRacingTimeMilliS(temp);

    quint8 hours = racingTimeMilliS() / 3600;
    quint8 minutes = (racingTimeMilliS() - hours*3600) / 60;
    quint8 seconds = (racingTimeMilliS() - hours*3600 - minutes*60);

    QString strHours = "";
    QString strMinutes = "";
    QString strSeconds = "";

    if(hours < 10){
        strHours = "0" + QString::number(hours);
    }
    else{
        strHours = QString::number(hours);
    }
    if(minutes < 10){
        strMinutes = "0" + QString::number(minutes);
    }
    else{
        strMinutes = QString::number(minutes);
    }
    if(seconds < 10){
        strSeconds = "0" + QString::number(seconds);
    }
    else{
        strSeconds = QString::number(seconds);
    }

//    QString timeString =  + ":" + QString::number(minutes) + ":" + QString::number(seconds);
    qDebug() << strHours + ":" + strMinutes + ":" + strSeconds;
    setRacingTime(strMinutes + ":" + strSeconds);
}

KartRpi_KartStatusModel::KartRpi_KartStatusModel(QObject *parent) : QObject(parent)
{

}
