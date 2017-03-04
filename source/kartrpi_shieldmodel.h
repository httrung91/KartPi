#ifndef KARTRPI_SHIELDMODEL_H
#define KARTRPI_SHIELDMODEL_H

#include <QObject>
#include <QTimer>

#include <QDebug>

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"

#define KARTRPI_SHIELDMODEL KartRpi_ShieldModel::Instance()

class KartRpi_ShieldModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 shieldCount READ shieldCount WRITE setShieldCount NOTIFY shieldCountChanged)
    Q_PROPERTY(bool isShieldEnabled READ isShieldEnabled WRITE setIsShieldEnabled NOTIFY isShieldEnabledChanged)
    Q_PROPERTY(QString eventTimeLimit READ eventTimeLimit WRITE setEventTimeLimit NOTIFY eventTimeLimitChanged)
    Q_PROPERTY(bool isShieldOn READ isShieldOn WRITE setIsShieldOn NOTIFY isShieldOnChanged)

public:
    static KartRpi_ShieldModel &Instance(void);

    void init();
    void enabledShield();
    void turnOnShield();

    quint8 shieldCount() const
    {
        return m_shieldCount;
    }

    bool isShieldEnabled() const
    {
        return m_isShieldEnabled;
    }

    QString eventTimeLimit() const
    {
        return m_eventTimeLimit;
    }

    bool isShieldOn() const
    {
        return m_isShieldOn;
    }

signals:

    void shieldCountChanged(quint8 shieldCount);

    void isShieldEnabledChanged(bool isShieldEnabled);

    void eventTimeLimitChanged(QString eventTimeLimit);

    void isShieldOnChanged(bool isShieldOn);

public slots:

    void onShieldEnabledTimerTrigger();
    void updateShieldTimer();

    void setShieldCount(quint8 shieldCount)
    {
        if (m_shieldCount == shieldCount)
            return;

        m_shieldCount = shieldCount;
        emit shieldCountChanged(shieldCount);
    }

    void setIsShieldEnabled(bool isShieldEnabled)
    {
        if (m_isShieldEnabled == isShieldEnabled)
            return;

        m_isShieldEnabled = isShieldEnabled;
        emit isShieldEnabledChanged(isShieldEnabled);
    }

    void setEventTimeLimit(QString eventTimeLimit)
    {
        if (m_eventTimeLimit == eventTimeLimit)
            return;

        m_eventTimeLimit = eventTimeLimit;
        emit eventTimeLimitChanged(eventTimeLimit);
    }

    void setIsShieldOn(bool isShieldOn)
    {
        if (m_isShieldOn == isShieldOn)
            return;

        m_isShieldOn = isShieldOn;
        emit isShieldOnChanged(isShieldOn);
    }

private:
    explicit KartRpi_ShieldModel(QObject *parent = 0);

    quint8 m_shieldCount;
    bool m_isShieldEnabled;
    QString m_eventTimeLimit;

    QTimer *m_shieldEnabledTimer;
    QTimer *m_updateShieldTimerS;

    bool m_isShieldOn;
};

#endif // KARTRPI_SHIELDMODEL_H
