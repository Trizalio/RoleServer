#ifndef CITEMMANAGER_H
#define CITEMMANAGER_H

#include <items/shealshot.h>
#include <items/sairlock.h>
#include <items/saircell.h>
#include <QDebug>

class CItemManager
{
public:
    CItemManager();

    static IItem* parseItem(SItem Item);
};

#endif // CITEMMANAGER_H
