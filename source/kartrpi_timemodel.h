#ifndef KARTRPI_TIMEMODEL_H
#define KARTRPI_TIMEMODEL_H

#include <QObject>

#define KARTRPI_TIMEMODEL KartRpi_TimeModel::Instane()

class KartRpi_TimeModel : public QObject
{
    Q_OBJECT
public:
    static KartRpi_TimeModel &Instane(void);

    void init();

signals:

public slots:

private:
    explicit KartRpi_TimeModel(QObject *parent = 0);

};

#endif // KARTRPI_TIMEMODEL_H
