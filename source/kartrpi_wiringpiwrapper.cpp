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
    qDebug() << "Set Up Interrupt callback!\n";
   KARTRPI_CONSOLE.appendConsoleData("Set Up Interrupt callback!");
#ifdef TARGET_BUILD
//    if(arg_pinNumber == PIN_5){
//        wiringPiISR(arg_pinNumber,INT_EDGE_RISING, interruptCallBack);
//    }
//    else if(arg_pinNumber == PIN_6){
//        wiringPiISR(arg_pinNumber,INT_EDGE_RISING, interruptCallBack2);
//    }
//    else{
//        //Do nothing
//    }
   switch (arg_pinNumber) {
   case PIN_6:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interruptCallBack2);
       break;
   case PIN_22:
       wiringPiISR(arg_pinNumber,INT_EDGE_RISING, interrupt_pin22);
       break;
   case PIN_24:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interrupt_pin24);
       break;
   case PIN_25:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interrupt_pin25);
       break;
   case PIN_27:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interrupt_pin27);
       break;
   case PIN_28:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interrupt_pin28);
       break;
   case PIN_29:
       wiringPiISR(arg_pinNumber,INT_EDGE_FALLING, interrupt_pin29);
       break;
   default:
       break;
   }

#endif
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
    //KARTRPI_ENGINE.callbackFromInterrupt2();
    KARTRPI_ENGINE.callbackFromHitbyLaser();
}

void KartRpi_WiringPiWrapper::interrupt_pin22()
{
    KARTRPI_ENGINE.callbackFromHitbyLaser();
}

void KartRpi_WiringPiWrapper::interrupt_pin24()
{
    KARTRPI_ENGINE.callbackFromLaserBeacon();
}

void KartRpi_WiringPiWrapper::interrupt_pin25()
{
    KARTRPI_ENGINE.callbackFromShieldBeacon();
}

void KartRpi_WiringPiWrapper::interrupt_pin27()
{
    KARTRPI_ENGINE.callbackFromSpeedBeacon();
}

void KartRpi_WiringPiWrapper::interrupt_pin28()
{
    KARTRPI_ENGINE.callbackFromBombBeacon();
}

void KartRpi_WiringPiWrapper::interrupt_pin29()
{
    KARTRPI_ENGINE.callbackFromTimeBeacon();
}
