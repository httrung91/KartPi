#ifndef KARTRPI_LASERMODEL_H
#define KARTRPI_LASERMODEL_H

#include <QObject>
#include <QTimer>

#include <QDebug>

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"

#define KARTRPI_LASERMODEL KartRpi_LaserModel::Instance()

class KartRpi_LaserModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 numberOfRounds READ numberOfRounds WRITE setNumberOfRounds NOTIFY numberOfRoundsChanged)
    Q_PROPERTY(bool isGunEnabled READ isGunEnabled WRITE setIsGunEnabled NOTIFY isGunEnabledChanged)
    Q_PROPERTY(quint8 numberOfShots READ numberOfShots WRITE setNumberOfShots NOTIFY numberOfShotsChanged)
    Q_PROPERTY(QString eventTimeLimit READ eventTimeLimit WRITE setEventTimeLimit NOTIFY eventTimeLimitChanged)

public:
    static KartRpi_LaserModel &Instance(void);

    void init();

    void shootLaser();

    quint8 numberOfRounds() const
    {
        return m_numberOfRounds;
    }

    bool isGunEnabled() const
    {
        return m_isGunEnabled;
    }

    quint8 numberOfShots() const
    {
        return m_numberOfShots;
    }

    QString eventTimeLimit() const
    {
        return m_eventTimeLimit;
    }

signals:

    void numberOfRoundsChanged(quint8 numberOfRounds);

    void isGunEnabledChanged(bool isGunEnabled);

    void numberOfShotsChanged(quint8 numberOfShots);

    void eventTimeLimitChanged(QString eventTimeLimit);

public slots:

    void enabledLaserGun();

    void onGunEnabledTimerTrigger();

    void updateLaserTimer();

    void setNumberOfRounds(quint8 numberOfRounds)
    {
        if (m_numberOfRounds == numberOfRounds)
            return;

        m_numberOfRounds = numberOfRounds;
        emit numberOfRoundsChanged(numberOfRounds);
    }

    void setIsGunEnabled(bool isGunEnabled)
    {
        if (m_isGunEnabled == isGunEnabled)
            return;

        m_isGunEnabled = isGunEnabled;
        emit isGunEnabledChanged(isGunEnabled);
    }

    void setNumberOfShots(quint8 numberOfShots)
    {
        if (m_numberOfShots == numberOfShots)
            return;

        m_numberOfShots = numberOfShots;
        emit numberOfShotsChanged(numberOfShots);
    }

    void setEventTimeLimit(QString eventTimeLimit)
    {
        if (m_eventTimeLimit == eventTimeLimit)
            return;

        m_eventTimeLimit = eventTimeLimit;
        emit eventTimeLimitChanged(eventTimeLimit);
    }

private:
    explicit KartRpi_LaserModel(QObject *parent = 0);


    quint8 m_numberOfRounds;
    bool m_isGunEnabled;
    quint8 m_numberOfShots;
    QString m_eventTimeLimit;

    QTimer *m_gunEnabledTimer;
    QTimer *m_updateLaserTimerS;

    int m_timerDuration;
    quint8 m_shotMax;
};

#endif // KARTRPI_LASERMODEL_H
