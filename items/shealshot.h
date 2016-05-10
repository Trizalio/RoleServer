#ifndef SHEALSHOT_H
#define SHEALSHOT_H

#include "iitem.h"

#define TYPE_HEALSHOT "HealShot"
#define USE_HEALSHOT "Принять"

class SHealShot : public IItem
{
public:
    SHealShot();

    QString getName() override;
    QString getType() override;
    QStringList getActions() override;
    QJsonObject getItemJson() override;


};

#endif // SHEALSHOT_H
