#include "saircell.h"

SAirCell::SAirCell(int nSize):
    m_nSize(nSize)
{
    eType = AirCell;
}

QString SAirCell::getName()
{
    return "Блок регенерации кислорода";
}

QString SAirCell::getType()
{
    return "Ресурс работы " + QString::number(m_nSize/60) + " минут";
}

QStringList SAirCell::getActions()
{
    QStringList Result;
    Result << USE_AIRCELL;
    return Result;
}

QJsonObject SAirCell::getItemJson()
{
    QJsonObject jUser;
    jUser.insert("type", TYPE_AIRCELL);
    jUser.insert("size", m_nSize);

    return jUser;
}
