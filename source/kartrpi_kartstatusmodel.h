#ifndef KARTRPI_KARTSTATUSMODEL_H
#define KARTRPI_KARTSTATUSMODEL_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_engine.h"

#define KARTRPI_KARTSTATUSMODEL KartRpi_KartStatusModel::Instance()

class KartRpi_KartStatusModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 speedLimit READ speedLimit WRITE setSpeedLimit NOTIFY speedLimitChanged)
    Q_PROPERTY(QString racingTime READ racingTime WRITE setRacingTime NOTIFY racingTimeChanged)
    Q_PROPERTY(bool isUnderShieldEffect READ isUnderShieldEffect WRITE setIsUnderShieldEffect NOTIFY isUnderShieldEffectChanged)
    Q_PROPERTY(bool isUnderSpeedEffect READ isUnderSpeedEffect WRITE setIsUnderSpeedEffect NOTIFY isUnderSpeedEffectChanged)
    Q_PROPERTY(bool isUnderBombEffect READ isUnderBombEffect WRITE setIsUnderBombEffect NOTIFY isUnderBombEffectChanged)
    Q_PROPERTY(bool isUsingLaserGun READ isUsingLaserGun WRITE setIsUsingLaserGun NOTIFY isUsingLaserGunChanged)
    Q_PROPERTY(quint64 racingTimeMilliS READ racingTimeMilliS WRITE setRacingTimeMilliS NOTIFY racingTimeMilliSChanged)
    Q_PROPERTY(qint32 racingScore READ racingScore WRITE setRacingScore NOTIFY racingScoreChanged)

public:
    static KartRpi_KartStatusModel &Instance(void);

    void init();

    void startTimeLapCounter();
    void stopTimeLapCounter();
    void decreaseTimeLap();

    void hitByLaser();

    quint8 speedLimit() const
    {
        return m_speedLimit;
    }

    QString racingTime() const
    {
        return m_racingTime;
    }

    bool isUnderShieldEffect() const
    {
        return m_isUnderShieldEffect;
    }

    bool isUnderSpeedEffect() const
    {
        return m_isUnderSpeedEffect;
    }

    bool isUnderBombEffect() const
    {
        return m_isUnderBombEffect;
    }

    quint64 racingTimeMilliS() const
    {
        return m_racingTimeMilliS;
    }

    bool isUsingLaserGun() const
    {
        return m_isUsingLaserGun;
    }

    qint32 racingScore() const
    {
        return m_racingScore;
    }

signals:

    void speedLimitChanged(quint8 speedLimit);

    void racingTimeChanged(QString racingTime);

    void isUnderShieldEffectChanged(bool isUnderShieldEffect);

    void isUnderSpeedEffectChanged(bool isUnderSpeedEffect);

    void isUnderBombEffectChanged(bool isUnderBombEffect);

    void racingTimeMilliSChanged(quint64 racingTimeMilliS);

    void isUsingLaserGunChanged(bool isUsingLaserGun);

    void racingScoreChanged(qint32 racingScore);

public slots:

    void updateTimeLap();

    void setSpeedLimit(quint8 speedLimit)
    {
        if (m_speedLimit == speedLimit)
            return;

        m_speedLimit = speedLimit;
        emit speedLimitChanged(speedLimit);
    }

    void setRacingTime(QString racingTime)
    {
        if (m_racingTime == racingTime)
            return;

        m_racingTime = racingTime;
        emit racingTimeChanged(racingTime);
    }

    void setIsUnderShieldEffect(bool isUnderShieldEffect)
    {
        if (m_isUnderShieldEffect == isUnderShieldEffect)
            return;

        m_isUnderShieldEffect = isUnderShieldEffect;
        emit isUnderShieldEffectChanged(isUnderShieldEffect);
    }

    void setIsUnderSpeedEffect(bool isUnderSpeedEffect)
    {
        if (m_isUnderSpeedEffect == isUnderSpeedEffect)
            return;

        m_isUnderSpeedEffect = isUnderSpeedEffect;
        emit isUnderSpeedEffectChanged(isUnderSpeedEffect);
    }

    void setIsUnderBombEffect(bool isUnderBombEffect)
    {
        if (m_isUnderBombEffect == isUnderBombEffect)
            return;

        m_isUnderBombEffect = isUnderBombEffect;
        emit isUnderBombEffectChanged(isUnderBombEffect);
    }

    void setRacingTimeMilliS(quint64 racingTimeMilliS)
    {
        if (m_racingTimeMilliS == racingTimeMilliS)
            return;

        m_racingTimeMilliS = racingTimeMilliS;
        emit racingTimeMilliSChanged(racingTimeMilliS);
    }

    void setIsUsingLaserGun(bool isUsingLaserGun)
    {
        if (m_isUsingLaserGun == isUsingLaserGun)
            return;

        m_isUsingLaserGun = isUsingLaserGun;
        emit isUsingLaserGunChanged(isUsingLaserGun);
    }

    void setRacingScore(qint32 racingScore)
    {
        if (m_racingScore == racingScore)
            return;

        m_racingScore = racingScore;
        emit racingScoreChanged(racingScore);
    }

private:
    explicit KartRpi_KartStatusModel(QObject *parent = 0);

    quint8 m_speedLimit;
    QString m_racingTime;
    bool m_isUnderShieldEffect;
    bool m_isUnderSpeedEffect;
    bool m_isUnderBombEffect;

    QTimer *m_racingTimer;
    quint64 m_racingTimeMilliS;
    bool m_isUsingLaserGun;
    qint32 m_racingScore;
};

#endif // KARTRPI_KARTSTATUSMODEL_H
