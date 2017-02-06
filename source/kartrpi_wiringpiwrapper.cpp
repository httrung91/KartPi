#include "kartrpi_wiringpiwrapper.h"

#include "kartrpi_engine.h"

KartRpi_WiringPiWrapper &KartRpi_WiringPiWrapper::Instance()
{
    static KartRpi_WiringPiWrapper instance;
    return instance;
}

void KartRpi_WiringPiWrapper::init()
{
    qDebug() << "Init WiringWrapper class ....";
#ifdef TARGET_BUILD
    int re = wiringPiSetup();
    if ( re == -1){
        qDebug() << "CRITICAL: WiringPi Setup Error!";
        KartRpi_ConsoleModel::Instance().appendConsoleData("CRITICAL: WiringPi Setup Error!");
        return;
    }   
#endif
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
#ifdef TARGET_BUILD
    pinMode(arg_pinNumber, arg_pinMode);
#endif
}

void KartRpi_WiringPiWrapper::writeValueToPin(int arg_pinNumber, int arg_val)
{
    if(arg_pinNumber < 0 || arg_pinNumber > 31){
        qDebug() << "ERROR: Pin is not available!\n";
        KartRpi_ConsoleModel::Instance().appendConsoleData("ERROR: Pin is not available!");
        return;
    }
#ifdef TARGET_BUILD
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
#else
    Q_UNUSED(arg_val);
#endif
}

void KartRpi_WiringPiWrapper::setInterruptPin(int arg_pinNumber)
{
    if(arg_pinNumber == PIN_5){
        wiringPiISR(arg_pinNumber,INT_EDGE_RISING, interruptCallBack);
    }
    else if(arg_pinNumber == PIN_6){
        wiringPiISR(arg_pinNumber,INT_EDGE_RISING, interruptCallBack2);
    }
    else{
        //Do nothing
    }
}

int KartRpi_WiringPiWrapper::readValueFromPin(int arg_pinNumber)
{
#ifdef TARGET_BUILD
    return digitalRead(arg_pinNumber);
#else
    Q_UNUSED(arg_pinNumber);
    return 0;
#endif
}

KartRpi_WiringPiWrapper::KartRpi_WiringPiWrapper(QObject *parent) : QObject(parent)
{

}

void KartRpi_WiringPiWrapper::interruptCallBack()
{
    KARTRPI_ENGINE.callbackFromInterrupt();
}

void KartRpi_WiringPiWrapper::interruptCallBack2()
{
    KARTRPI_ENGINE.callbackFromInterrupt2();
}
