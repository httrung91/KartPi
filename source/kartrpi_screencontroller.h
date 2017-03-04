#ifndef KARTRPI_SCREENCONTROLLER_H
#define KARTRPI_SCREENCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"
#include "kartrpi_engine.h"
#include "kartpi_commondefs.h"

#include "kartrpi_lasermodel.h"
#include "kartrpi_shieldmodel.h"
#include "kartrpi_speedmodel.h"
#include "kartrpi_bombmodel.h"
#include "kartrpi_timemodel.h"
#include "kartrpi_kartstatusmodel.h"

#define KARTRPI_SCREENCONTROLLER KartRpi_ScreenController::Instance()

class KartRpi_ScreenController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString screenUrl READ screenUrl WRITE setScreenUrl NOTIFY screenUrlChanged)

public:
    static KartRpi_ScreenController &Instance(void);
    void init();

    //handle user action
    Q_INVOKABLE void handleFireBtnPress();
    Q_INVOKABLE void handleSpeedBtnPress();
    Q_INVOKABLE void handleShieldBtnPress();
    Q_INVOKABLE void startRacing();

    //test
    Q_INVOKABLE void handleReadInputTest();

    //change Screen
    Q_INVOKABLE void handleChangeScreen(QString arg_screenUrl);

    //handle simulating beacon
    Q_INVOKABLE void handleLaserBeaconPress();
    Q_INVOKABLE void handleShieldBeaconPress();
    Q_INVOKABLE void handleSpeedBeaconPress();
    Q_INVOKABLE void handleBombBeaconPress();
    Q_INVOKABLE void handleTimeBeaconPress();

    QString screenUrl() const
    {
        return m_screenUrl;
    }

signals:

    void screenUrlChanged(QString screenUrl);

public slots:

void setScreenUrl(QString screenUrl)
{
    if (m_screenUrl == screenUrl)
        return;

    m_screenUrl = screenUrl;
    emit screenUrlChanged(screenUrl);
}

private:
    explicit KartRpi_ScreenController(QObject *parent = 0);

QString m_screenUrl;
};

#endif // KARTRPI_SCREENCONTROLLER_H
