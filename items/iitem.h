#ifndef IITEM_H
#define IITEM_H

#include "orm/sql_objects/sitem.h"
#include <QStringList>

enum ItemTypes
{
    Undefined,
    HealShot,
    Airlock,
    AirCell
};

class IItem
{
public:
    SItem toItem();
    virtual QString getName() = 0;
    virtual QString getType() = 0;
    virtual QStringList getActions() = 0;
    virtual QJsonObject getItemJson() = 0;

    ItemTypes eType = Undefined;
};

#endif // IITEM_H
