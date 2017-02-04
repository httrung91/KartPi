#include "kartrpi_engine.h"

#include "kartrpi_screencontroller.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"

KartRpi_Engine &KartRpi_Engine::Instance()
{
    static KartRpi_Engine instance;
    return instance;
}

void KartRpi_Engine::init(QQmlApplicationEngine *arg_engine)
{
    qDebug() << "Init KartRpi Engine... ";
    m_engine = arg_engine;

    //Init module instance
    KartRpi_ScreenController::Instance().init();
    KartRpi_ConsoleModel::Instance().init();
    KartRpi_WiringPiWrapper::Instance().init();

    KartRpi_WiringPiWrapper::Instance().setPinMode(0, 1);
    KartRpi_WiringPiWrapper::Instance().setPinMode(1, 1);
    KartRpi_WiringPiWrapper::Instance().setPinMode(2, 1);

    m_fireTimer = new QTimer();
    m_fireTimer->setInterval(1000);
    m_speedTimer = new QTimer();
    m_speedTimer->setInterval(1000);
    m_shieldTimer = new QTimer();
    m_shieldTimer->setInterval(1000);

    //Set Context to qml
    m_engine->rootContext()->setContextProperty("SCREENCONTROLLER", &KartRpi_ScreenController::Instance());
    m_engine->rootContext()->setContextProperty("VIEWCONSOLEMODEL", &KartRpi_ConsoleModel::Instance());
}

void KartRpi_Engine::connectSignalsAndSlots()
{
    QObject::connect(m_fireTimer,SIGNAL(timeout()),this,SLOT(onFireTimerTriggered()));
    QObject::connect(m_speedTimer,SIGNAL(timeout()),this,SLOT(onSpeedTimerTriggered()));
    QObject::connect(m_shieldTimer,SIGNAL(timeout()),this,SLOT(onShieldTimerTriggered()));
}

void KartRpi_Engine::startKartTimer(int arg)
{
    switch (arg) {
    case 0:
        m_fireTimer->start();
        break;
    case 1:
        m_speedTimer->start();
        break;
    case 2:
        m_shieldTimer->start();
        break;
    default:
        break;
    }
}

void KartRpi_Engine::onFireTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(0,0);
}

void KartRpi_Engine::onSpeedTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(1,0);
}

void KartRpi_Engine::onShieldTimerTriggered()
{
    KartRpi_WiringPiWrapper::Instance().writeValueToPin(2,0);
}

KartRpi_Engine::KartRpi_Engine(QObject *parent) : QObject(parent)
{

}
