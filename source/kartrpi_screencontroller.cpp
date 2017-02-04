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
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(0,1);
    KartRpi_Engine::Instance().startKartTimer(0);
}

void KartRpi_ScreenController::handleSpeedBtnPress()
{
    qDebug() << "Speed Button Pressed... ";
    KartRpi_ConsoleModel::Instance().appendConsoleData("Speed up >>>>>)))))");
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(1,1);
    KartRpi_Engine::Instance().startKartTimer(1);
}

void KartRpi_ScreenController::handleShieldBtnPress()
{
    qDebug() << "Shield Button Pressed... ";
    KartRpi_ConsoleModel::Instance().appendConsoleData("Shield up <><><><><>");
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(2,1);
    KartRpi_Engine::Instance().startKartTimer(2);
}

KartRpi_ScreenController::KartRpi_ScreenController(QObject *parent) : QObject(parent)
{

}
