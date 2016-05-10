#ifndef SAIRLOCK_H
#define SAIRLOCK_H

#include "iitem.h"

#define TYPE_AIRLOCK "Airlock"
#define USE_AIRLOCK "Пройти"

class SAirlock : public IItem
{
public:
    SAirlock();

    QString getName() override;
    QString getType() override;
    QStringList getActions() override;
    QJsonObject getItemJson() override;
};

#endif // SAIRLOCK_H
