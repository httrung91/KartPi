#include "kartrpi_wiringpiwrapper.h"

KartRpi_WiringPiWrapper &KartRpi_WiringPiWrapper::Instance()
{
    static KartRpi_WiringPiWrapper instance;
    return instance;
}

void KartRpi_WiringPiWrapper::init()
{
    qDebug() << "Init WiringWrapper class ....";
    int re = wiringPiSetup();
    if ( re == -1){
        qDebug() << "CRITICAL: WiringPi Setup Error!";
        KartRpi_ConsoleModel::Instance().appendConsoleData("CRITICAL: WiringPi Setup Error!");
        return;
    }
}

void KartRpi_WiringPiWrapper::setPinMode(int arg_pinNumber, int arg_pinMode)
{
    if(arg_pinNumber < 0 || arg_pinNumber > 31){
        qDebug() << "ERROR: Pin is not available!\n";
        KartRpi_ConsoleModel::Instance().appendConsoleData("ERROR: Pin is not available!");
        return;
    }
    if(arg_pinMode < 0 || arg_pinMode > 6){
        qDebug() << "ERROR: Pin Mode is not available!\n";
        KartRpi_ConsoleModel::Instance().appendConsoleData("ERROR: Pin Mode is not available!");
        return;
    }
    pinMode(arg_pinNumber, arg_pinMode);
}

void KartRpi_WiringPiWrapper::writeValueToPin(int arg_pinNumber, int arg_val)
{
    if(arg_pinNumber < 0 || arg_pinNumber > 31){
        qDebug() << "ERROR: Pin is not available!\n";
        KartRpi_ConsoleModel::Instance().appendConsoleData("ERROR: Pin is not available!");
        return;
    }
    switch (arg_val) {
    case LOW:
        digitalWrite(arg_pinNumber, LOW);
        break;
    case HIGH:
        digitalWrite(arg_pinNumber, HIGH);
        break;
    default:
        break;
    }
}

KartRpi_WiringPiWrapper::KartRpi_WiringPiWrapper(QObject *parent) : QObject(parent)
{

}
