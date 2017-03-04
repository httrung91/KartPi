#include "kartrpi_lasermodel.h"

#include "kartrpi_kartstatusmodel.h"

KartRpi_LaserModel &KartRpi_LaserModel::Instance()
{
    static KartRpi_LaserModel instance;
    return instance;
}

void KartRpi_LaserModel::init()
{
    m_numberOfRounds = 0;
    m_isGunEnabled = false;
    m_numberOfShots = 0;
    m_eventTimeLimit = "0";

    m_shotMax = 0;
    m_timerDuration = 0;

    m_gunEnabledTimer = new QTimer(this);
    m_gunEnabledTimer->setSingleShot(true);

    m_updateLaserTimerS = new QTimer(this);
    m_updateLaserTimerS->setInterval(1000);

    connect(m_gunEnabledTimer, SIGNAL(timeout()), this, SLOT(onGunEnabledTimerTrigger()));
    connect(m_updateLaserTimerS, SIGNAL(timeout()), this, SLOT(updateLaserTimer()));
}

void KartRpi_LaserModel::enabledLaserGun()
{
    if(m_numberOfRounds > 1 ){
        return;
    }
    m_numberOfRounds++;
    setIsGunEnabled(true);
    m_numberOfShots += 10;
    m_timerDuration += 15000;
    m_shotMax += 10;
    m_gunEnabledTimer->setInterval(m_timerDuration);


    setEventTimeLimit(QString::number(m_timerDuration/1000));
    emit numberOfRoundsChanged(m_numberOfRounds);
    //emit isGunEnabledChanged(m_isGunEnabled);
    emit numberOfShotsChanged(m_numberOfShots);

}

void KartRpi_LaserModel::shootLaser()
{
    if(!m_isGunEnabled){
        return;
    }
    if(m_numberOfShots == m_shotMax){
        qDebug() << "First shot: " << m_numberOfShots << ", " << m_shotMax;
        m_gunEnabledTimer->start();
        m_updateLaserTimerS->start();
        KARTRPI_KARTSTATUSMODEL.setIsUsingLaserGun(true);
        m_numberOfShots--;
    }
    else if(m_numberOfShots == 1){
        qDebug() << "Last shot: " << m_numberOfShots << ", " << m_shotMax;
        m_numberOfShots--;
        m_gunEnabledTimer->stop();
        this->onGunEnabledTimerTrigger();
    }
    else{
        qDebug() << "Keep shooting: " << m_numberOfShots << ", " << m_shotMax;
        m_numberOfShots--;
    }

    emit numberOfShotsChanged(m_numberOfShots);

    KARTRPI_WIRINGPI.writeValueToPin(PIN_0,HIGH);
    KARTRPI_CONSOLE.appendConsoleData("Fire Gun >>=====+>>");
    if(m_gunEnabledTimer->isActive()){
        qDebug() << "Laser Timer is running";
    }
}

void KartRpi_LaserModel::onGunEnabledTimerTrigger()
{
    qDebug() << "Round end, find more laser beacon!!!";
    if(m_gunEnabledTimer->isActive()){
        qDebug() << "Stop Laser timer";
        m_gunEnabledTimer->stop();
    }
    m_updateLaserTimerS->stop();
    m_timerDuration = 0;
    setNumberOfRounds(0);
    setIsGunEnabled(false);
    setNumberOfShots(0);
    setEventTimeLimit("-");
    KARTRPI_KARTSTATUSMODEL.setIsUsingLaserGun(false);
    m_shotMax = 0;
}

void KartRpi_LaserModel::updateLaserTimer()
{
    qDebug() << "Update Laser Timer...";
    int remainingTime = m_gunEnabledTimer->remainingTime();

    int temp = remainingTime / 1000;

    setEventTimeLimit(QString::number(temp));
}

KartRpi_LaserModel::KartRpi_LaserModel(QObject *parent) : QObject(parent)
{

}
