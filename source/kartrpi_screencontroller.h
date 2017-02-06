#ifndef KARTRPI_SCREENCONTROLLER_H
#define KARTRPI_SCREENCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"
#include "kartrpi_engine.h"
#include "kartpi_commondefs.h"

class KartRpi_ScreenController : public QObject
{
    Q_OBJECT
public:
    static KartRpi_ScreenController &Instance(void);
    void init();

    Q_INVOKABLE void handleFireBtnPress();
    Q_INVOKABLE void handleSpeedBtnPress();
    Q_INVOKABLE void handleShieldBtnPress();
    Q_INVOKABLE void handleReadInputTest();

signals:

public slots:

private:
    explicit KartRpi_ScreenController(QObject *parent = 0);

};

#endif // KARTRPI_SCREENCONTROLLER_H
