#include "kartrpi_screencontroller.h"

KartRpi_ScreenController &KartRpi_ScreenController::Instance()
{
    static KartRpi_ScreenController instance;
    return instance;
}

void KartRpi_ScreenController::init()
{
    qDebug() << "Init Screen Controller... ";
}

void KartRpi_ScreenController::handleFireBtnPress()
{
    qDebug() << "Fire Button Pressed... ";
    KartRpi_ConsoleModel::Instance().appendConsoleData("Fire Gun >>=====+>>");
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_0,HIGH);
    KartRpi_Engine::Instance().startKartTimer(0);
}

void KartRpi_ScreenController::handleSpeedBtnPress()
{
    qDebug() << "Speed Button Pressed... ";
    KartRpi_ConsoleModel::Instance().appendConsoleData("Speed up >>>>>)))))");
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_2,HIGH);
    KartRpi_Engine::Instance().startKartTimer(1);
}

void KartRpi_ScreenController::handleShieldBtnPress()
{
    qDebug() << "Shield Button Pressed... ";
    KartRpi_ConsoleModel::Instance().appendConsoleData("Shield up <><><><><>");
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(PIN_3,HIGH);
    KartRpi_Engine::Instance().startKartTimer(2);
}

void KartRpi_ScreenController::handleReadInputTest()
{
    qDebug() << "Read Input Test Press...";
    int val = KARTRPI_WIRINGPI.readValueFromPin(PIN_4);
    KARTRPI_CONSOLE.appendConsoleData(QString("READ INPUT TEST: %1").arg(val));
}

KartRpi_ScreenController::KartRpi_ScreenController(QObject *parent) : QObject(parent)
{

}
