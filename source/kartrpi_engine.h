#ifndef KARTRPI_ENGINE_H
#define KARTRPI_ENGINE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QDebug>

class KartRpi_Engine : public QObject
{
    Q_OBJECT
public:
    static KartRpi_Engine &Instance(void);
    void init(QQmlApplicationEngine *arg_engine);
    void connectSignalsAndSlots();
    void startKartTimer(int arg);

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
