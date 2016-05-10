#include "sairlock.h"

SAirlock::SAirlock()
{
    eType = Airlock;
}

QString SAirlock::getName()
{
    return "Шлюз";
}

QString SAirlock::getType()
{
    return "Соединяет станцию и открытое пространство планеты";
}

QStringList SAirlock::getActions()
{
    QStringList Result;
    Result << USE_AIRLOCK;
    return Result;
}

QJsonObject SAirlock::getItemJson()
{
    QJsonObject jUser;
    jUser.insert("type", TYPE_AIRLOCK);

    return jUser;
}

