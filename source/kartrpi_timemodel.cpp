#include "kartrpi_timemodel.h"

KartRpi_TimeModel &KartRpi_TimeModel::Instane()
{
    static KartRpi_TimeModel instance;
    return instance;
}

void KartRpi_TimeModel::init()
{

}

KartRpi_TimeModel::KartRpi_TimeModel(QObject *parent) : QObject(parent)
{

}
