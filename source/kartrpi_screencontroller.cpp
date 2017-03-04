#include "kartrpi_screencontroller.h"

KartRpi_ScreenController &KartRpi_ScreenController::Instance()
{
    static KartRpi_ScreenController instance;
    return instance;
}

void KartRpi_ScreenController::init()
{
    qDebug() << "Init Screen Controller... ";
    setScreenUrl("qrc:/Screens/Screen_KartRpiWelcome.qml");
}

void KartRpi_ScreenController::handleFireBtnPress()
{
    qDebug() << "Fire Button Pressed... ";
//    KartRpi_ConsoleModel::Instance().appendConsoleData("Fire Gun >>=====+>>");
//    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_0,HIGH);
    //KartRpi_Engine::Instance().startKartTimer(0);
    KARTRPI_LASERMODEL.shootLaser();
    KARTRPI_ENGINE.startKartTimer(0);
}

void KartRpi_ScreenController::handleSpeedBtnPress()
{
    qDebug() << "Speed Button Pressed... ";
    //KartRpi_ConsoleModel::Instance().appendConsoleData("Speed up >>>>>)))))");
//    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_2,HIGH);
//    KartRpi_Engine::Instance().startKartTimer(1);
    KARTRPI_SPEEDMODEL.turnOnSpeed();
}

void KartRpi_ScreenController::handleShieldBtnPress()
{
    qDebug() << "Shield Button Pressed... ";
//    KartRpi_ConsoleModel::Instance().appendConsoleData("Shield up <><><><><>");
//    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_3,HIGH);
//    KartRpi_Engine::Instance().startKartTimer(2);
    KARTRPI_SHIELDMODEL.turnOnShield();
}

void KartRpi_ScreenController::startRacing()
{
    KARTRPI_KARTSTATUSMODEL.startTimeLapCounter();
}

void KartRpi_ScreenController::handleReadInputTest()
{
    qDebug() << "Read Input Test Press...";
    int val = KARTRPI_WIRINGPI.readValueFromPin(PIN_6);
    KARTRPI_CONSOLE.appendConsoleData(QString("READ INPUT TEST: %1").arg(val));
}

void KartRpi_ScreenController::handleChangeScreen(QString arg_screenUrl)
{
    setScreenUrl(arg_screenUrl);
}

void KartRpi_ScreenController::handleLaserBeaconPress()
{
    KARTRPI_ENGINE.callbackFromLaserBeacon();
}

void KartRpi_ScreenController::handleShieldBeaconPress()
{
    KARTRPI_ENGINE.callbackFromShieldBeacon();
}

void KartRpi_ScreenController::handleSpeedBeaconPress()
{
    KARTRPI_ENGINE.callbackFromSpeedBeacon();
}

void KartRpi_ScreenController::handleBombBeaconPress()
{
    KARTRPI_ENGINE.callbackFromBombBeacon();
}

void KartRpi_ScreenController::handleTimeBeaconPress()
{
    KARTRPI_ENGINE.callbackFromTimeBeacon();
}

KartRpi_ScreenController::KartRpi_ScreenController(QObject *parent) : QObject(parent)
{

}
