#include "kartrpi_speedmodel.h"

#include "kartrpi_bombmodel.h"
#include "kartrpi_kartstatusmodel.h"

KartRpi_SpeedModel &KartRpi_SpeedModel::Instance()
{
    static KartRpi_SpeedModel instance;
    return instance;
}

void KartRpi_SpeedModel::init()
{
    setSpeedCount(0);
    setIsSpeedEnabled(false);
    setIsUsingSpeedBonus(false);
    setEventTimeLimit("0");

    m_timerDuration = 0;
    m_speedEnabledTimer = new QTimer(this);
    m_speedEnabledTimer->setSingleShot(true);
    m_speedEnabledTimer->setInterval(15000);

    m_updateSpeedTimerS = new QTimer(this);
    m_updateSpeedTimerS->setInterval(1000);

    connect(m_speedEnabledTimer, SIGNAL(timeout()), this, SLOT(onSpeedEnabledTimerTrigger()));
    connect(m_updateSpeedTimerS, SIGNAL(timeout()), this, SLOT(updateSpeedTimer()));
}

void KartRpi_SpeedModel::enableSpeedButton()
{
    if(m_speedCount > 0){
        return;
    }

    qDebug() << "Enable Speed ...";
    setSpeedCount(1);
    setIsSpeedEnabled(true);
    setEventTimeLimit("15");
}

void KartRpi_SpeedModel::turnOnSpeed()
{
    if(m_speedCount < 1 || m_isUsingSpeedBonus == true){
        return;
    }

    if(KARTRPI_KARTSTATUSMODEL.isUnderBombEffect()){
        //return to normal speed
        qDebug() << "Remove Bomb Effect ....";
        KARTRPI_CONSOLE.appendConsoleData("Remove Bomb Effect ....");
        KARTRPI_BOMBMODEL.onBombEffectTimerTrigger();
        //onSpeedEnabledTimerTrigger();
        setSpeedCount(0);
        setEventTimeLimit("0");
        setIsSpeedEnabled(false);
    }
    else if(KARTRPI_KARTSTATUSMODEL.isUnderSpeedEffect()){
        qDebug() << "Speeding already ...";
        KARTRPI_CONSOLE.appendConsoleData("Speeding already ...");
    }
    else{
        qDebug() << "Speeding Up ....";
        setIsUsingSpeedBonus(true);
        setSpeedCount(0);
        setIsSpeedEnabled(false);
        KARTRPI_KARTSTATUSMODEL.setSpeedLimit(50);
        KARTRPI_KARTSTATUSMODEL.setIsUnderSpeedEffect(true);
        KARTRPI_WIRINGPI.writeValueToPin(PIN_3,HIGH);
        KARTRPI_CONSOLE.appendConsoleData("Speeding up <><><><><>");

        m_speedEnabledTimer->start();
        m_updateSpeedTimerS->start();
    }
}

void KartRpi_SpeedModel::onSpeedEnabledTimerTrigger()
{
    qDebug() << "Speed Time expired, find more beacon ...";
    if(m_speedEnabledTimer->isActive()){
        m_speedEnabledTimer->stop();
    }
    m_updateSpeedTimerS->stop();
    setSpeedCount(0);
    setIsSpeedEnabled(false);
    setIsUsingSpeedBonus(false);
    setEventTimeLimit("0");
    KARTRPI_KARTSTATUSMODEL.setSpeedLimit(35);
    KARTRPI_KARTSTATUSMODEL.setIsUnderSpeedEffect(false);
    KARTRPI_WIRINGPI.writeValueToPin(PIN_3,LOW);
    KARTRPI_CONSOLE.appendConsoleData("Speeding off <><><><><>");
}

void KartRpi_SpeedModel::updateSpeedTimer()
{
    qDebug() << "Update Speed Timer...";
    int remainingTime = m_speedEnabledTimer->remainingTime();

    int temp = remainingTime / 1000;

    setEventTimeLimit(QString::number(temp));
}

KartRpi_SpeedModel::KartRpi_SpeedModel(QObject *parent) : QObject(parent)
{

}
