#include "sgroup.h"

std::string SGroup::typeToString(SGroup::eGroupType eType)
{
    if(eType == SGroup::HIDDEN)
    {
        return std::string("hidden");
    }
    else if(eType == SGroup::NORMAL)
    {
        return std::string("normal");
    }
    else if(eType == SGroup::PUBLIC)
    {
        return std::string("public");
    }
    else if(eType == SGroup::LAB)
    {
        return std::string("lab");
    }
    return std::string();
}

SGroup::eGroupType SGroup::stringToType(std::string sType)
{
    if(sType == std::string("hidden"))
    {
        return SGroup::HIDDEN;
    }
    else if(sType == std::string("normal"))
    {
        return SGroup::NORMAL;
    }
    else if(sType == std::string("public"))
    {
        return SGroup::PUBLIC;
    }
    else if(sType == std::string("lab"))
    {
        return SGroup::LAB;
    }
    return SGroup::HIDDEN;
}

SGroup::SGroup(){}

SGroup::SGroup(int nId, int nParentId, std::string sName, std::string sDescription, std::string sType):
    m_nId(nId),
    m_nParentId(nParentId),
    m_sName(sName),
    m_sDescription(sDescription),
    m_eType(stringToType(sType))
{

}

SGroup::SGroup(int nParentId, std::string sName, std::string sDescription, SGroup::eGroupType eType):
    m_nParentId(nParentId),
    m_sName(sName),
    m_sDescription(sDescription),
    m_eType(eType)
{}

QJsonObject SGroup::getJsonObject()
{
    QJsonObject jCellObject;
    jCellObject.insert("Id", QJsonValue(m_nId));
    jCellObject.insert("Name", QJsonValue(m_sName.c_str()));
    jCellObject.insert("Description", QJsonValue(m_sDescription.c_str()));
    jCellObject.insert("Type", QJsonValue(typeToString(m_eType).c_str()));
    return jCellObject;
}
