#include "ctickmanager.h"

CTickManager::CTickManager(COrm *pOrm):
    m_pOrm(pOrm)
{

}

void CTickManager::tick()
{
//    qDebug() << __FUNCTION__;
    std::vector<SUserStat> UserStats = m_pOrm->selectUserStatsAll();
//    drainOxygen(UserStats);
    cureStun(UserStats);
    update(UserStats);
}

void CTickManager::update(std::vector<SUserStat>& aUserStats)
{
//    qDebug() << __FUNCTION__;
    for(std::vector<SUserStat>::iterator it = aUserStats.begin(); it != aUserStats.end(); ++it)
    {
        if(it->m_bChanged)
        {
            m_pOrm->updateUserStat(*it);
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            emit statusUpdate(Player.m_nId);
        }
    }
}

void CTickManager::cureStun(std::vector<SUserStat>& aUserStats)
{
//    qDebug() << __FUNCTION__;
    for(std::vector<SUserStat>::iterator it = aUserStats.begin(); it != aUserStats.end(); ++it)
    {
        if(it->m_nStun > 0)
        {
            it->m_bChanged = true;
            it->m_nStun -= 1;
            if(it->m_nStun <= 0)
            {
                SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
                emit statusChange("Вы пришли в себя!", Player.m_nId);
            }
        }
        if(it->m_nAir >= 0)
        {
            it->m_bChanged = true;
            it->m_nAir -= 1;
            if(it->m_nAir == 4 * 60)
            {
//                it->m_nHp = 0;
//                m_pOrm->modifyHealthUserId(-100, it->m_nId);
                SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
                emit statusChange("Из-за кислородного голодания Вы испытываете головокружение, слабость, тошноту!",
                                  Player.m_nId);
            }
            else if(it->m_nAir == 2 * 60)
            {
                SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
                it->m_nHp = 1;
//                m_pOrm->modifyHealthUserId(-100, it->m_nId);
                emit statusChange("Из-за кислородного голодания Вы получили повреждение лёгких и не способны самостоятельно передвигаться!",
                                  Player.m_nId);
            }
            else if(it->m_nAir == 0)
            {
                SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
                it->m_nHp = 0;
//                m_pOrm->modifyHealthUserId(-100, it->m_nId);
                emit statusChange("Вы задохнулись!", Player.m_nId);
            }
            /*if(it->m_nAirId > 0)
            {
                SItem Item = m_pOrm->findItemById(it->m_nAirId);
                if(Item.m_nId > 0)
                {
                    qDebug() << "item found";
                    IItem* pItem = CItemManager::parseItem(Item);
                    if(pItem == 0)
                    {
                        qDebug() << "got 0 pointer from parser";
                    }
                    else if(pItem->eType == AirCell)
                    {
                        SAirCell* pAirCell = (SAirCell*)pItem;
                        pAirCell->m_nSize -= DEFAULT_AIR_SEC - it->m_nAir;
                        it->m_nAir = DEFAULT_AIR_SEC;
                        if(pAirCell->m_nSize < 0)
                        {
                            it->m_nAir += pAirCell->m_nSize;
                            pAirCell->m_nSize = 0;
                            it->m_nAirId = 0;
                        }
                    }
                }
            }*/
        }

    }
}

void CTickManager::drainOxygen(std::vector<SUserStat>& aUserStats)
{
    for(std::vector<SUserStat>::iterator it = aUserStats.begin(); it != aUserStats.end(); ++it)
    {
        if(it->m_nAir == 0)
        {
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            m_pOrm->modifyHealthUserId(-100, it->m_nId);
            statusChange("Вы задохнулись!", Player.m_nId);
        }
        else if(it->m_nAir == DEFAULT_AIR_SEC/30) /// 0.5
        {
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            statusChange("Вы задыхаетесь, в глазах темнеет, Вы едва можете ползти!", Player.m_nId);
        }
        else if(it->m_nAir == DEFAULT_AIR_SEC/10) /// 1.5
        {
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            statusChange("Вы задыхаетесь, Вас качает, Вы с трудом можете идти!", Player.m_nId);
        }
        else if(it->m_nAir == DEFAULT_AIR_SEC/5) /// 3
        {
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            statusChange("Вам тяжело дышать, вы чувствуете слабость, не можете бегать!", Player.m_nId);
        }
        else if(it->m_nAir == DEFAULT_AIR_SEC/2) /// 7.5
        {
            SPlayer Player = m_pOrm->findPlayerByUserId(it->m_nId);
            statusChange("Ваше дыхание участилось!", Player.m_nId);
        }
    }
}

