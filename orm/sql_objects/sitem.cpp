#include "sitem.h"

SItem::SItem()
{

}

SItem::SItem(QString sJsonData):
    m_sJsonData(sJsonData)
{

}

SItem::SItem(int m_nId, QString sJsonData, QString sHash):
    m_nId(m_nId),
    m_sJsonData(sJsonData),
    m_sHash(sHash)
{

}

QJsonObject SItem::getJsonObject()
{
    QJsonObject jCellObject;
    jCellObject.insert("Id", QJsonValue(m_nId));
    return jCellObject;
}

