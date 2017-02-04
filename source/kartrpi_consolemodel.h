#ifndef KARTRPI_CONSOLEMODEL_H
#define KARTRPI_CONSOLEMODEL_H

#include <QObject>
#include <QDebug>

class KartRpi_ConsoleModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString consoleData READ consoleData WRITE setConsoleData NOTIFY consoleDataChanged)

public:
    static KartRpi_ConsoleModel &Instance(void);
    void init();

    void clearConsoleData();
    void appendConsoleData(QString arg);

    QString consoleData() const
    {
        return m_consoleData;
    }

signals:

    void consoleDataChanged(QString consoleData);

public slots:

void setConsoleData(QString consoleData)
{
    if (m_consoleData == consoleData)
        return;

    m_consoleData = consoleData;
    emit consoleDataChanged(consoleData);
}

private:
    explicit KartRpi_ConsoleModel(QObject *parent = 0);

QString m_consoleData;
};

#endif // KARTRPI_CONSOLEMODEL_H
