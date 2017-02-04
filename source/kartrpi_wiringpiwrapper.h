#ifndef KARTRPI_WIRINGPIWRAPPER_H
#define KARTRPI_WIRINGPIWRAPPER_H

#include <QObject>
#include <QDebug>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringSerial.h>
#include <wiringShift.h>

#include "kartrpi_consolemodel.h"

class KartRpi_WiringPiWrapper : public QObject
{
    Q_OBJECT
public:
    static KartRpi_WiringPiWrapper &Instance(void);
    void init();
    void setPinMode(int arg_pinNumber, int arg_pinMode);
    void writeValueToPin(int arg_pinNumber,int arg_val);

signals:

public slots:

private:
    explicit KartRpi_WiringPiWrapper(QObject *parent = 0);
};

#endif // KARTRPI_WIRINGPIWRAPPER_H
