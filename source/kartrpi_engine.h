#ifndef KARTRPI_ENGINE_H
#define KARTRPI_ENGINE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QDebug>

#include "kartpi_commondefs.h"

#define KARTRPI_ENGINE KartRpi_Engine::Instance()

class KartRpi_Engine : public QObject
{
    Q_OBJECT
public:
    static KartRpi_Engine &Instance(void);
    void init(QQmlApplicationEngine *arg_engine);
    void connectSignalsAndSlots();
    void startKartTimer(int arg);

    //callBack sequence
    void callbackFromHitbyLaser();
    void callbackFromLaserBeacon();
    void callbackFromShieldBeacon();
    void callbackFromSpeedBeacon();
    void callbackFromBombBeacon();
    void callbackFromTimeBeacon();

    void callbackFromInterrupt();
    void callbackFromInterrupt2();

signals:
    void hitByBomb();

public slots:
    void onDebounceLaserBeacon();

    void onFireTimerTriggered();
    void onSpeedTimerTriggered();
    void onShieldTimerTriggered();

private:
    explicit KartRpi_Engine(QObject *parent = 0);

    //Qml control
    QQmlApplicationEngine *m_engine;
    QTimer *m_fireTimer;

    QTimer *m_debounceLaserBeacon;

    int m_testIRSCount;
};

#endif // KARTRPI_ENGINE_H
