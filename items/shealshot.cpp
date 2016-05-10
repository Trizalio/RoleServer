#include "shealshot.h"

SHealShot::SHealShot()
{
    eType = HealShot;
}

QString SHealShot::getName()
{
    return "Капсула с препаратом";
}

QString SHealShot::getType()
{
    return "Лекарство";
}

QStringList SHealShot::getActions()
{
    QStringList Result;
    Result << USE_HEALSHOT;
    return Result;
}

QJsonObject SHealShot::getItemJson()
{
    QJsonObject jUser;
    jUser.insert("type", TYPE_HEALSHOT);

    return jUser;
}

