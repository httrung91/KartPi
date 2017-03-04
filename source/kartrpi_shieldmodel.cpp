#include "kartrpi_shieldmodel.h"

#include "kartrpi_kartstatusmodel.h"

KartRpi_ShieldModel &KartRpi_ShieldModel::Instance()
{
    static KartRpi_ShieldModel instance;
    return instance;
}

void KartRpi_ShieldModel::init()
{
    setShieldCount(0);
    setIsShieldEnabled(false);
    setIsShieldOn(false);
    setEventTimeLimit("0");

    m_shieldEnabledTimer = new QTimer(this);
    m_shieldEnabledTimer->setSingleShot(true);
    m_shieldEnabledTimer->setInterval(10000);

    m_updateShieldTimerS = new QTimer(this);
    m_updateShieldTimerS->setInterval(1000);

    connect(m_shieldEnabledTimer, SIGNAL(timeout()), this, SLOT(onShieldEnabledTimerTrigger()));
    connect(m_updateShieldTimerS, SIGNAL(timeout()), this, SLOT(updateShieldTimer()));
}

void KartRpi_ShieldModel::enabledShield()
{
    qDebug() << "Got Shield, Enable button" ;

    if(m_shieldCount > 0){
        return;
    }
    setShieldCount(1);
    setIsShieldEnabled(true);
    setEventTimeLimit("10");
}

void KartRpi_ShieldModel::turnOnShield()
{

    if(m_shieldCount < 1 || KARTRPI_KARTSTATUSMODEL.isUnderShieldEffect() == true){
        return;
    }

    qDebug() << "Turn on shield .....";
    KARTRPI_CONSOLE.appendConsoleData("Turn on shield .....");
    setIsShieldOn(true);
    setShieldCount(0);
    setIsShieldEnabled(false);

    KARTRPI_WIRINGPI.writeValueToPin(PIN_2,HIGH);

    KARTRPI_KARTSTATUSMODEL.setIsUnderShieldEffect(true);
    KARTRPI_CONSOLE.appendConsoleData("Shield up <><><><><>");

    m_shieldEnabledTimer->start();
    m_updateShieldTimerS->start();
}

void KartRpi_ShieldModel::onShieldEnabledTimerTrigger()
{
    qDebug() << "Shield Time expired, find more beacon ....";
    KARTRPI_CONSOLE.appendConsoleData("Shield Time expired, find more beacon ....");
    if(m_shieldEnabledTimer->isActive()){
        m_shieldEnabledTimer->stop();
    }
    m_updateShieldTimerS->stop();
    KARTRPI_WIRINGPI.writeValueToPin(PIN_2,LOW);
    KARTRPI_KARTSTATUSMODEL.setIsUnderShieldEffect(false);
    KARTRPI_CONSOLE.appendConsoleData("Shield off <><><><><>");
    setIsShieldOn(false);
}

void KartRpi_ShieldModel::updateShieldTimer()
{
    qDebug() << "Update Shield Timer...";
    int remainingTime = m_shieldEnabledTimer->remainingTime();

    int temp = remainingTime / 1000;

    setEventTimeLimit(QString::number(temp));
}

KartRpi_ShieldModel::KartRpi_ShieldModel(QObject *parent) : QObject(parent)
{

}
