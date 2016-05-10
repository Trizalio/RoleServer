#ifndef SAIRCELL_H
#define SAIRCELL_H

#include "iitem.h"

#define TYPE_AIRCELL "Aircell"
#define USE_AIRCELL "Подключить к своему скафандру"

#define DEFAULT_AIRCELL_SIZE_SEC 3600

class SAirCell : public IItem
{
public:
    SAirCell(int nSize = DEFAULT_AIRCELL_SIZE_SEC);

    QString getName() override;
    QString getType() override;
    QStringList getActions() override;
    QJsonObject getItemJson() override;

    int m_nSize;
//private:
};


#endif // SAIRCELL_H
