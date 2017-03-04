#ifndef KARTRPI_WIRINGPIWRAPPER_H
#define KARTRPI_WIRINGPIWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#ifdef TARGET_BUILD
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringSerial.h>
#include <wiringShift.h>
#endif

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"

#define KARTRPI_WIRINGPI KartRpi_WiringPiWrapper::Instance()

class KartRpi_WiringPiWrapper : public QObject
{
    Q_OBJECT
public:
    static KartRpi_WiringPiWrapper &Instance(void);
    void init();
    void setPinMode(int arg_pinNumber, int arg_pinMode);
    void writeValueToPin(int arg_pinNumber,int arg_val);
    void setInterruptPin(int arg_pinNumber);
    int readValueFromPin(int arg_pinNumber);

signals:

public slots:

private:
    explicit KartRpi_WiringPiWrapper(QObject *parent = 0);

    //test
    static void interruptCallBack();
    static void interruptCallBack2();

    //input pin
    static void interrupt_pin22(); //hitted by laser
    static void interrupt_pin24(); //laser
    static void interrupt_pin25(); //shield
    static void interrupt_pin27(); //speed
    static void interrupt_pin28(); //bomb
    static void interrupt_pin29(); //time

};

#endif // KARTRPI_WIRINGPIWRAPPER_H
