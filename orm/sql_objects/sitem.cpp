#include "sitem.h"

SItem::SItem()
{

}

SItem::SItem(std::string sJsonData):
    m_sJsonData(sJsonData)
{

}

SItem::SItem(int m_nId, std::string sJsonData, std::string sHash):
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

