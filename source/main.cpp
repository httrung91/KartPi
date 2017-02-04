#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "kartrpi_engine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KartRpi_Engine::Instance().init(&engine);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    KartRpi_Engine::Instance().connectSignalsAndSlots();

    return app.exec();
}
