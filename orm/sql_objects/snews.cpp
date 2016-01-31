#include "snews.h"

SNews::SNews()
{

}

SNews::SNews(int nId,
                int nRoleId,
                std::string sCreatedDatetime,
                std::string sSubject,
                std::string sText,
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
                std::string sCreatedDatetime,
                std::string sSubject,
                std::string sText,
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
    jCellObject.insert("Datetime", QJsonValue(m_sCreatedDatetime.c_str()));
    jCellObject.insert("Subject", QJsonValue(m_sSubject.c_str()));
    jCellObject.insert("Text", QJsonValue(m_sText.c_str()));
    jCellObject.insert("Shared", QJsonValue(m_bShared));
    return jCellObject;

}
