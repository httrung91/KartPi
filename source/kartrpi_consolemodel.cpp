#include "kartrpi_consolemodel.h"

KartRpi_ConsoleModel &KartRpi_ConsoleModel::Instance()
{
    static KartRpi_ConsoleModel instance;
    return instance;
}

void KartRpi_ConsoleModel::init()
{
    qDebug() << "Init Console Model ...";
    setConsoleData("Welcome to KartRpi v0.1\n");
}

void KartRpi_ConsoleModel::appendConsoleData(QString arg)
{
    QString str = QString("").append(m_consoleData).append(">> ").append(arg).append("\n");
    setConsoleData(str);
}

void KartRpi_ConsoleModel::clearConsoleData()
{
    setConsoleData("");
}

KartRpi_ConsoleModel::KartRpi_ConsoleModel(QObject *parent) : QObject(parent)
{
    m_consoleData = "";
}
