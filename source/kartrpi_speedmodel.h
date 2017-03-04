#ifndef KARTRPI_SPEEDMODEL_H
#define KARTRPI_SPEEDMODEL_H

#include <QObject>
#include <QTimer>

#include <QDebug>

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"

#define KARTRPI_SPEEDMODEL KartRpi_SpeedModel::Instance()

class KartRpi_SpeedModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 speedCount READ speedCount WRITE setSpeedCount NOTIFY speedCountChanged)
    Q_PROPERTY(bool isSpeedEnabled READ isSpeedEnabled WRITE setIsSpeedEnabled NOTIFY isSpeedEnabledChanged)
    Q_PROPERTY(bool isUsingSpeedBonus READ isUsingSpeedBonus WRITE setIsUsingSpeedBonus NOTIFY isUsingSpeedBonusChanged)
    Q_PROPERTY(QString eventTimeLimit READ eventTimeLimit WRITE setEventTimeLimit NOTIFY eventTimeLimitChanged)

public:
    static KartRpi_SpeedModel &Instance(void);

    void init();
    void enableSpeedButton();
    void turnOnSpeed();

    quint8 speedCount() const
    {
        return m_speedCount;
    }

    bool isSpeedEnabled() const
    {
        return m_isSpeedEnabled;
    }

    bool isUsingSpeedBonus() const
    {
        return m_isUsingSpeedBonus;
    }

    QString eventTimeLimit() const
    {
        return m_eventTimeLimit;
    }

signals:

    void speedCountChanged(quint8 speedCount);

    void isSpeedEnabledChanged(bool isSpeedEnabled);

    void isUsingSpeedBonusChanged(bool isUsingSpeedBonus);

    void eventTimeLimitChanged(QString eventTimeLimit);

public slots:
    void onSpeedEnabledTimerTrigger();
    void updateSpeedTimer();

    void setSpeedCount(quint8 speedCount)
    {
        if (m_speedCount == speedCount)
            return;

        m_speedCount = speedCount;
        emit speedCountChanged(speedCount);
    }

    void setIsSpeedEnabled(bool isSpeedEnabled)
    {
        if (m_isSpeedEnabled == isSpeedEnabled)
            return;

        m_isSpeedEnabled = isSpeedEnabled;
        emit isSpeedEnabledChanged(isSpeedEnabled);
    }

    void setIsUsingSpeedBonus(bool isUsingSpeedBonus)
    {
        if (m_isUsingSpeedBonus == isUsingSpeedBonus)
            return;

        m_isUsingSpeedBonus = isUsingSpeedBonus;
        emit isUsingSpeedBonusChanged(isUsingSpeedBonus);
    }

    void setEventTimeLimit(QString eventTimeLimit)
    {
        if (m_eventTimeLimit == eventTimeLimit)
            return;

        m_eventTimeLimit = eventTimeLimit;
        emit eventTimeLimitChanged(eventTimeLimit);
    }

private:
    explicit KartRpi_SpeedModel(QObject *parent = 0);
    quint8 m_speedCount;
    bool m_isSpeedEnabled;
    bool m_isUsingSpeedBonus;
    QString m_eventTimeLimit;

    QTimer *m_speedEnabledTimer;
    QTimer *m_updateSpeedTimerS;

    int m_timerDuration;
};

#endif // KARTRPI_SPEEDMODEL_H
