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
    void callbackFromInterrupt();
    void callbackFromInterrupt2();

signals:

public slots:
    void onFireTimerTriggered();
    void onSpeedTimerTriggered();
    void onShieldTimerTriggered();

private:
    explicit KartRpi_Engine(QObject *parent = 0);

    //Qml control
    QQmlApplicationEngine *m_engine;
    QTimer *m_fireTimer;
    QTimer *m_speedTimer;
    QTimer *m_shieldTimer;
};

#endif // KARTRPI_ENGINE_H
