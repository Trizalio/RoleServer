#include "suserstat.h"

SUserStat::SUserStat()
{

}

SUserStat::SUserStat(int nHpMax, int nHp, int nPp, int nAir, int nAirId):
    m_nHpMax(nHpMax),
    m_nHp(nHp),

    m_nPp(nPp),

    m_nAir(nAir),
    m_nAirId(nAirId)
{

}

SUserStat::SUserStat(int nId, int nHpMax, int nHp, int nPp, int nAir, int nAirId, int nStun):
    m_nId(nId),

    m_nHpMax(nHpMax),
    m_nHp(nHp),

    m_nPp(nPp),

    m_nAir(nAir),
    m_nAirId(nAirId),

    m_nStun(nStun)
{

}

QJsonObject SUserStat::getJsonObject()
{
    QJsonObject jUserStat;

    jUserStat.insert("Id", m_nId);
    jUserStat.insert("HpMax",m_nHpMax);
    jUserStat.insert("Hp",m_nHp);
    jUserStat.insert("Pp",m_nPp);
    jUserStat.insert("Air",m_nAir);
    jUserStat.insert("AirId",m_nAirId);
    jUserStat.insert("Stun",m_nStun);

    return jUserStat;
}

