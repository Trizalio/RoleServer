#include "splayer.h"

SPlayer::SPlayer(){}

SPlayer::SPlayer(std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

SPlayer::SPlayer(int nUserId, std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_nUserId(nUserId),
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

SPlayer::SPlayer(int nId, int nUserId, std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_nId(nId),
    m_nUserId(nUserId),
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

QJsonObject SPlayer::getJsonObject()
{

    QJsonObject jPlayer;

    jPlayer.insert("Id", m_nId);
    jPlayer.insert("UserId", m_nUserId);
    jPlayer.insert("Name",m_sName.c_str());
    jPlayer.insert("Surname",m_sSurname.c_str());
    jPlayer.insert("Patronymic",m_sPatronymic.c_str());
    jPlayer.insert("Nick",m_sNick.c_str());
    jPlayer.insert("BirthDate",m_sBirthDate.c_str());
    jPlayer.insert("Quenta",m_sQuenta.c_str());
    jPlayer.insert("Admin",m_bAdmin);

    return jPlayer;
}

