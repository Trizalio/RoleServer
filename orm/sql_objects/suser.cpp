#include "suser.h"



SUser::SUser(){}

SUser::SUser(std::string sName, std::string sSurname, std::string sPatronymic, std::string sBirthDate, std::string sProfession, std::string sDescription):
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sBirthDate(sBirthDate),
    m_sProfession(sProfession),
    m_sDescription(sDescription)
{}

SUser::SUser(int nId, std::string sName, std::string sSurname, std::string sPatronymic, std::string sBirthDate, std::string sProfession, std::string sDescription):
    m_nId(nId),
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sBirthDate(sBirthDate),
    m_sProfession(sProfession),
    m_sDescription(sDescription)
{}


QJsonObject SUser::getJsonObject()
{
    QJsonObject jUser;

    jUser.insert("Id", m_nId);
    jUser.insert("Name",m_sName.c_str());
    jUser.insert("Surname",m_sSurname.c_str());
    jUser.insert("Patronymic",m_sPatronymic.c_str());
    jUser.insert("BirthDate",m_sBirthDate.c_str());
    jUser.insert("Profession",m_sProfession.c_str());
    jUser.insert("Description",m_sDescription.c_str());

    return jUser;
}
