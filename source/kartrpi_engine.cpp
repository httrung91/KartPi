#include "kartrpi_engine.h"

#include "kartrpi_screencontroller.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"

#include "kartrpi_lasermodel.h"
#include "kartrpi_shieldmodel.h"
#include "kartrpi_speedmodel.h"
#include "kartrpi_bombmodel.h"
#include "kartrpi_timemodel.h"
#include "kartrpi_kartstatusmodel.h"

KartRpi_Engine &KartRpi_Engine::Instance()
{
    static KartRpi_Engine instance;
    return instance;
}

void KartRpi_Engine::init(QQmlApplicationEngine *arg_engine)
{
    qDebug() << "Init KartRpi Engine... ";
    m_engine = arg_engine;

    //Init module instance
    KARTRPI_SCREENCONTROLLER.init();
    KARTRPI_CONSOLE.init();
    KARTRPI_WIRINGPI.init();

    KARTRPI_LASERMODEL.init();
    KARTRPI_SHIELDMODEL.init();
    KARTRPI_SPEEDMODEL.init();
    KARTRPI_BOMBMODEL.init();
    KARTRPI_TIMEMODEL.init();
    KARTRPI_KARTSTATUSMODEL.init();

    KARTRPI_WIRINGPI.setPinMode(PIN_0, OUTPUT);
    KARTRPI_WIRINGPI.setPinMode(PIN_2, OUTPUT);
    KARTRPI_WIRINGPI.setPinMode(PIN_3, OUTPUT);
    KARTRPI_WIRINGPI.setPinMode(PIN_4, OUTPUT);
    KARTRPI_WIRINGPI.setPinMode(PIN_5, OUTPUT);

    KARTRPI_WIRINGPI.setPinMode(PIN_6,INPUT);
    KARTRPI_WIRINGPI.setPinMode(PIN_22,INPUT); //hit
    KARTRPI_WIRINGPI.setPinMode(PIN_24,INPUT); //Laser
    KARTRPI_WIRINGPI.setPinMode(PIN_25,INPUT); //Shield
    KARTRPI_WIRINGPI.setPinMode(PIN_27,INPUT); //Speed
    KARTRPI_WIRINGPI.setPinMode(PIN_28,INPUT); //Bomb
    KARTRPI_WIRINGPI.setPinMode(PIN_29,INPUT); //Time

    //    KARTRPI_WIRINGPI.setInterruptPin(PIN_5);
    //    KARTRPI_WIRINGPI.setInterruptPin(PIN_6);

    KARTRPI_WIRINGPI.setInterruptPin(PIN_6);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_22);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_24);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_25);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_27);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_28);
    KARTRPI_WIRINGPI.setInterruptPin(PIN_29);

    m_fireTimer = new QTimer();
    m_fireTimer->setInterval(1000);

    m_debounceLaserBeacon = new QTimer();
//    m_debounceLaserBeacon->setSingleShot(true);
    m_debounceLaserBeacon->setInterval(50);



    //Set Context to qml
    m_engine->rootContext()->setContextProperty("SCREENCONTROLLER", &KARTRPI_SCREENCONTROLLER);
    m_engine->rootContext()->setContextProperty("VIEWCONSOLEMODEL", &KARTRPI_CONSOLE);
    m_engine->rootContext()->setContextProperty("LASERMODEL", &KARTRPI_LASERMODEL);
    m_engine->rootContext()->setContextProperty("SHIELDMODEL", &KARTRPI_SHIELDMODEL);
    m_engine->rootContext()->setContextProperty("SPEEDMODEL", &KARTRPI_SPEEDMODEL);
    m_engine->rootContext()->setContextProperty("BOMBMODEL", &KARTRPI_BOMBMODEL);
    m_engine->rootContext()->setContextProperty("TIMEMODEL", &KARTRPI_TIMEMODEL);
    m_engine->rootContext()->setContextProperty("KARTSTATUS", &KARTRPI_KARTSTATUSMODEL);

}

void KartRpi_Engine::connectSignalsAndSlots()
{
    QObject::connect(m_fireTimer,SIGNAL(timeout()),this,SLOT(onFireTimerTriggered()));
    QObject::connect(m_debounceLaserBeacon, SIGNAL(timeout()), this, SLOT(onDebounceLaserBeacon()));
    QObject::connect(this, SIGNAL(hitByBomb()), &KARTRPI_BOMBMODEL, SLOT(hitByBomb()));
}

void KartRpi_Engine::startKartTimer(int arg)
{
    switch (arg) {
    case 0:
        m_fireTimer->start();
        break;
    default:
        break;
    }
}

void KartRpi_Engine::callbackFromHitbyLaser()
{
    qDebug() << "Hit by Laser";
    KARTRPI_CONSOLE.appendConsoleData("Hit by Laser");
    qint32 currentScore = KARTRPI_KARTSTATUSMODEL.racingScore();
    if(KARTRPI_KARTSTATUSMODEL.isUnderShieldEffect()){
        currentScore += 2;
        KARTRPI_KARTSTATUSMODEL.setRacingScore(currentScore);
    }
    else{
        currentScore -= 2;
        KARTRPI_KARTSTATUSMODEL.setRacingScore(currentScore);
    }
}

void KartRpi_Engine::callbackFromLaserBeacon()
{
//    if(m_debounceLaserBeacon->isActive()){
//        return;
//    }
//    else{
        qDebug() << "Add Laser";
        KARTRPI_CONSOLE.appendConsoleData("Add Laser");
//        m_debounceLaserBeacon->start();
        KARTRPI_LASERMODEL.enabledLaserGun();
//    }
}

void KartRpi_Engine::callbackFromShieldBeacon()
{
    qDebug() << "Add Shield";
    KARTRPI_CONSOLE.appendConsoleData("Add Shield");
    KARTRPI_SHIELDMODEL.enabledShield();
}

void KartRpi_Engine::callbackFromSpeedBeacon()
{
    qDebug() << "Add Speed";
    KARTRPI_CONSOLE.appendConsoleData("Add Speed");
    KARTRPI_SPEEDMODEL.enableSpeedButton();
}

void KartRpi_Engine::callbackFromBombBeacon()
{
    qDebug() << "Hit by Bomb";
    KARTRPI_CONSOLE.appendConsoleData("Hit by Bomb");
    emit hitByBomb();
    //KARTRPI_BOMBMODEL.hitByBomb();
}

void KartRpi_Engine::callbackFromTimeBeacon()
{
    qDebug() << "Add Time Bonus";
    KARTRPI_CONSOLE.appendConsoleData("Add Time Bonus");
    KARTRPI_KARTSTATUSMODEL.decreaseTimeLap();
}

void KartRpi_Engine::callbackFromInterrupt()
{
    qDebug() << "Callback from WRPI Interrupt...";
    KARTRPI_CONSOLE.appendConsoleData("Interrupt from PIN5");
}

void KartRpi_Engine::callbackFromInterrupt2()
{
    m_testIRSCount++;
    qDebug() << "Callback from WRPI Interrupt..." << m_testIRSCount;
    KARTRPI_CONSOLE.appendConsoleData("Interrupt from PIN6" + QString::number(m_testIRSCount));
}

void KartRpi_Engine::onDebounceLaserBeacon()
{
//    KARTRPI_CONSOLE.appendConsoleData("Check to add laser");
//    if(KARTRPI_WIRINGPI.readValueFromPin(PIN_24) == 1){
//        KARTRPI_LASERMODEL.enabledLaserGun();
//    }
}

void KartRpi_Engine::onFireTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_0,LOW);
}

void KartRpi_Engine::onSpeedTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_2,LOW);
}

void KartRpi_Engine::onShieldTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_3,LOW);
}

KartRpi_Engine::KartRpi_Engine(QObject *parent) : QObject(parent)
{

}
