#include "snews.h"

SNews::SNews()
{

}

SNews::SNews(int nId,
                int nRoleId,
                QString sCreatedDatetime,
                QString sSubject,
                QString sText,
                bool bAnonymously,
                bool bShared):
    m_nId(nId),
    m_nRoleId(nRoleId),
    m_sCreatedDatetime(sCreatedDatetime),
    m_sSubject(sSubject),
    m_sText(sText),
    m_bAnonymously(bAnonymously),
    m_bShared(bShared)
{

}
SNews::SNews(int nRoleId,
                QString sCreatedDatetime,
                QString sSubject,
                QString sText,
                bool bAnonymously,
                bool bShared):
    m_nRoleId(nRoleId),
    m_sCreatedDatetime(sCreatedDatetime),
    m_sSubject(sSubject),
    m_sText(sText),
    m_bAnonymously(bAnonymously),
    m_bShared(bShared)
{

}

QJsonObject SNews::getJsonObject()
{
    QJsonObject jCellObject;
    jCellObject.insert("Id", QJsonValue(m_nId));
    jCellObject.insert("Datetime", QJsonValue(m_sCreatedDatetime));
    jCellObject.insert("Subject", QJsonValue(m_sSubject));
    jCellObject.insert("Text", QJsonValue(m_sText));
    jCellObject.insert("Shared", QJsonValue(m_bShared));
    return jCellObject;

}
