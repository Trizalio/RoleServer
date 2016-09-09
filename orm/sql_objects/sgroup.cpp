#include "sgroup.h"

QString SGroup::typeToString(SGroup::eGroupType eType)
{
    if(eType == SGroup::HIDDEN)
    {
        return QString("hidden");
    }
    else if(eType == SGroup::NORMAL)
    {
        return QString("normal");
    }
    else if(eType == SGroup::PUBLIC)
    {
        return QString("public");
    }
    else if(eType == SGroup::LAB)
    {
        return QString("lab");
    }
    return QString();
}

SGroup::eGroupType SGroup::stringToType(QString sType)
{
    if(sType == QString("hidden"))
    {
        return SGroup::HIDDEN;
    }
    else if(sType == QString("normal"))
    {
        return SGroup::NORMAL;
    }
    else if(sType == QString("public"))
    {
        return SGroup::PUBLIC;
    }
    else if(sType == QString("lab"))
    {
        return SGroup::LAB;
    }
    return SGroup::HIDDEN;
}

SGroup::SGroup(){}

SGroup::SGroup(int nId, int nParentId, QString sName, QString sDescription, QString sType):
    m_nId(nId),
    m_nParentId(nParentId),
    m_sName(sName),
    m_sDescription(sDescription),
    m_eType(stringToType(sType))
{

}

SGroup::SGroup(int nParentId, QString sName, QString sDescription, SGroup::eGroupType eType):
    m_nParentId(nParentId),
    m_sName(sName),
    m_sDescription(sDescription),
    m_eType(eType)
{}

QJsonObject SGroup::getJsonObject()
{
    QJsonObject jCellObject;
    jCellObject.insert("Id", QJsonValue(m_nId));
    jCellObject.insert("Name", QJsonValue(m_sName));
    jCellObject.insert("Description", QJsonValue(m_sDescription));
    jCellObject.insert("Type", QJsonValue(typeToString(m_eType)));
    return jCellObject;
}
