#include "kartrpi_bombmodel.h"

#include "kartrpi_speedmodel.h"
#include "kartrpi_kartstatusmodel.h"

KartRpi_BombModel &KartRpi_BombModel::Instance()
{
    static KartRpi_BombModel instance;
    return instance;
}

void KartRpi_BombModel::init()
{
    setBombCount(0);
    setIsUnderBombEffect(false);
    setEventTimeLimit("");

    m_bombEffectTimer = new QTimer();
    //sm_bombEffectTimer->setSingleShot(false);
    connect(m_bombEffectTimer, SIGNAL(timeout()), this, SLOT(onBombEffectTimerTrigger()));

    m_updateBombTimer = new QTimer(this);
    m_updateBombTimer->setInterval(1000);
    connect(m_updateBombTimer, SIGNAL(timeout()), this, SLOT(updateBombTimer()));
}

void KartRpi_BombModel::hitByBomb()
{
    if (KARTRPI_KARTSTATUSMODEL.isUnderSpeedEffect()){
        //Set Speed to normal
        qDebug() << "Speeding -> return to normal speed";
        KARTRPI_CONSOLE.appendConsoleData("Speeding -> return to normal speed");
        //KARTRPI_KARTSTATUSMODEL.setIsUnderSpeedEffect(false);
        //KARTRPI_KARTSTATUSMODEL.setSpeedLimit(35);
        KARTRPI_SPEEDMODEL.onSpeedEnabledTimerTrigger();
        return;
    }
    if(m_bombCount == 10){
        return;
    }

    if(m_bombCount == 0){
        qDebug() << "Hit by bomb!!!! ";
        KARTRPI_CONSOLE.appendConsoleData("Hit by bomb!!!! ");
        setBombCount(m_bombCount+1);
        m_bombEffectTimer->setInterval(15000);
        m_updateBombTimer->start();
    }
    else{
        qDebug() << "Hit by another bomb!!!";
        KARTRPI_CONSOLE.appendConsoleData("Hit by another bomb!!!");
        setBombCount(m_bombCount+1);
        int remainingTime = m_bombEffectTimer->remainingTime();
        remainingTime += 15000;
        m_bombEffectTimer->stop();
        m_bombEffectTimer->setInterval(remainingTime);
    }
    m_bombEffectTimer->start();
    setIsUnderBombEffect(true);
    KARTRPI_KARTSTATUSMODEL.setIsUnderBombEffect(true);
    KARTRPI_KARTSTATUSMODEL.setSpeedLimit(20);
    KARTRPI_WIRINGPI.writeValueToPin(PIN_4,HIGH);
}

void KartRpi_BombModel::onBombEffectTimerTrigger()
{
    qDebug() << "End Bomb Effect...";
    KARTRPI_CONSOLE.appendConsoleData("End Bomb Effect...");
    if(m_bombEffectTimer->isActive()){
        m_bombEffectTimer->stop();
    }
    m_updateBombTimer->stop();
    setIsUnderBombEffect(false);
    setBombCount(0);
    setEventTimeLimit("00:00");
    KARTRPI_KARTSTATUSMODEL.setIsUnderBombEffect(false);
    KARTRPI_KARTSTATUSMODEL.setSpeedLimit(35);
    KARTRPI_WIRINGPI.writeValueToPin(PIN_4,LOW);
}

void KartRpi_BombModel::updateBombTimer()
{
    qDebug() << "Update Bomb Timer...";
    int remainingTime = m_bombEffectTimer->remainingTime();

    int temp = remainingTime / 1000;

    quint8 minutes = temp / 60;
    quint8 seconds = (temp - minutes*60);

    QString strMinutes = "";
    QString strSeconds = "";

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

    qDebug() << strMinutes + ":" + strSeconds;
    setEventTimeLimit(strMinutes + ":" + strSeconds);
}

KartRpi_BombModel::KartRpi_BombModel(QObject *parent) : QObject(parent)
{

}
