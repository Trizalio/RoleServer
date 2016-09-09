#include "slore.h"

SLore::SLore()
{

}

SLore::SLore(QString sTitle, QString sText):
    m_sTitle(sTitle),
    m_sText(sText)
{

}

SLore::SLore(int nId, QString sTitle, QString sText):
    m_nId(nId),
    m_sTitle(sTitle),
    m_sText(sText)
{

}

QJsonObject SLore::getJsonObject()
{
    QJsonObject jCellObject;
    jCellObject.insert("Id", QJsonValue(m_nId));
    jCellObject.insert("Title", QJsonValue(m_sTitle));
    jCellObject.insert("Text", QJsonValue(m_sText));
    return jCellObject;

}

