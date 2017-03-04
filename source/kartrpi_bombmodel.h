#ifndef KARTRPI_BOMBMODEL_H
#define KARTRPI_BOMBMODEL_H

#include <QObject>
#include <QObject>
#include <QTimer>

#include <QDebug>

#include "kartpi_commondefs.h"
#include "kartrpi_consolemodel.h"
#include "kartrpi_wiringpiwrapper.h"



#define KARTRPI_BOMBMODEL KartRpi_BombModel::Instance()

class KartRpi_BombModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 bombCount READ bombCount WRITE setBombCount NOTIFY bombCountChanged)
    Q_PROPERTY(bool isUnderBombEffect READ isUnderBombEffect WRITE setIsUnderBombEffect NOTIFY isUnderBombEffectChanged)
    Q_PROPERTY(quint8 bombCount READ bombCount WRITE setBombCount NOTIFY bombCountChanged)
    Q_PROPERTY(QString eventTimeLimit READ eventTimeLimit WRITE setEventTimeLimit NOTIFY eventTimeLimitChanged)
    Q_PROPERTY(quint32 bombTimeSecond READ bombTimeSecond WRITE setBombTimeSecond NOTIFY bombTimeSecondChanged)

public:
    static KartRpi_BombModel &Instance(void);

    void init();


    quint8 bombCount() const
    {
        return m_bombCount;
    }

    bool isUnderBombEffect() const
    {
        return m_isUnderBombEffect;
    }

    QString eventTimeLimit() const
    {
        return m_eventTimeLimit;
    }

    quint32 bombTimeSecond() const
    {
        return m_bombTimeSecond;
    }

signals:

    void bombCountChanged(quint8 bombCount);

    void isUnderBombEffectChanged(bool isUnderBombEffect);

    void eventTimeLimitChanged(QString eventTimeLimit);

    void bombTimeSecondChanged(quint32 bombTimeSecond);

public slots:

    void onBombEffectTimerTrigger();
    void updateBombTimer();
    void hitByBomb();

    void setBombCount(quint8 bombCount)
    {
        if (m_bombCount == bombCount)
            return;

        m_bombCount = bombCount;
        emit bombCountChanged(bombCount);
    }

    void setIsUnderBombEffect(bool isUnderBombEffect)
    {
        if (m_isUnderBombEffect == isUnderBombEffect)
            return;

        m_isUnderBombEffect = isUnderBombEffect;
        emit isUnderBombEffectChanged(isUnderBombEffect);
    }

    void setEventTimeLimit(QString eventTimeLimit)
    {
        if (m_eventTimeLimit == eventTimeLimit)
            return;

        m_eventTimeLimit = eventTimeLimit;
        emit eventTimeLimitChanged(eventTimeLimit);
    }

    void setBombTimeSecond(quint32 bombTimeSecond)
    {
        if (m_bombTimeSecond == bombTimeSecond)
            return;

        m_bombTimeSecond = bombTimeSecond;
        emit bombTimeSecondChanged(bombTimeSecond);
    }

private:
    explicit KartRpi_BombModel(QObject *parent = 0);

    quint8 m_bombCount;
    bool m_isUnderBombEffect;
    QString m_eventTimeLimit;

    QTimer *m_bombEffectTimer;
    QTimer *m_updateBombTimer;
    quint32 m_bombTimeSecond;
};

#endif // KARTRPI_BOMBMODEL_H
