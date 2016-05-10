#include "cserverlogic.h"

CServerLogic::CServerLogic(COrm *pOrm):
    m_pOrm(pOrm)
{
    SHealShot HealShot;
    m_pOrm->insertItem(HealShot.toItem());
    SAirlock Airlock;
    m_pOrm->insertItem(Airlock.toItem());
}

//SPlayer CServerLogic::login(std::string sLogin, std::string sPassword)
//{
//    qDebug() << __FUNCTION__;
//    SPlayer Player = m_pOrm->findPlayerByLoginAndPassHash(sLogin, sPassword);
//    return Player;
//}
QPair<int, bool> CServerLogic::login(std::string sLogin, std::string sPassword)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerByLoginAndPassHash(sLogin, sPassword);
    return QPair<int, bool>(Player.m_nId, Player.m_bAdmin);
}

//SPlayer CServerLogic::getPlayerById(int nId)
//{
//    qDebug() << __FUNCTION__;
//    SPlayer Player = m_pOrm->findPlayerById(nId);

//    return Player;
//}

bool CServerLogic::CheckAdminByPlayerId(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nId);

    return Player.m_bAdmin;
}

QPair<int, bool> CServerLogic::getUserIdAndIsAdminByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nPlayerId);

    return QPair<int, bool>(Player.m_nUserId, Player.m_bAdmin);
}

int CServerLogic::getPlayerIdByUserId(int nUserId)
{
    SPlayer Player = m_pOrm->findPlayerByUserId(nUserId);
    return Player.m_nId;
}

QByteArray CServerLogic::getPlayerData(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nPlayerId);

    return Player.getJson();
}

QByteArray CServerLogic::getPlayersAll()
{
    qDebug() << __FUNCTION__;
    std::vector<SPlayer> aPlayers = m_pOrm->selectPlayersAll();

    QJsonArray jArray;
    for(size_t i = 0; i < aPlayers.size(); ++i)
    {
        QJsonValue jValue(aPlayers[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

QByteArray CServerLogic::getUserByIdVisibleByPlayerId(int nUserId, int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    CUser User;
    if(bIsAbdmin)
    {
        User = m_pOrm->getUserByIdVisibleByAdmin(nUserId);
    }
    else
    {
        User = m_pOrm->getUserByIdVisibleByUser(nUserId, nWatcherUserId);
    }
    return User.getJson();
}

QByteArray CServerLogic::getUsersAllData()
{
    qDebug() << __FUNCTION__;
    std::vector<SUser> Users = m_pOrm->selectUserAll();

    QJsonArray jArray;
    for(size_t i = 0; i < Users.size(); ++i)
    {
        QJsonValue jValue(Users[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

QByteArray CServerLogic::getUserStatusVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    SUserStat Stat = m_pOrm->findUserStatsById(nWatcherUserId);
    return Stat.getJson();
}

QByteArray CServerLogic::getProjectByIdVisibleByPlayerId(int nProjectId, int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    CGroup Group;
    if(bIsAbdmin)
    {
        Group = m_pOrm->getGroupInfoByIdVisibleByAdmin(nProjectId);
    }
    else
    {
        Group = m_pOrm->getGroupInfoByIdVisibleByUser(nProjectId, nWatcherUserId);
    }
    return Group.getJson();
}

QByteArray CServerLogic::getProjectsAllVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    std::vector<SGroup> aGroups;
    if(bIsAbdmin)
    {
        aGroups = m_pOrm->selectAllGroupsVisibleByAdmin();
    }
    else
    {
        aGroups = m_pOrm->selectAllGroupsVisibleByUser(nWatcherUserId);
    }
    qDebug() << aGroups.size();


    QJsonArray jArray;
    for(size_t i = 0; i < aGroups.size(); ++i)
    {
        QJsonValue jValue(aGroups[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}
/// deprecated
//QByteArray CServerLogic::getProjectsAllData()
//{
//    qDebug() << __FUNCTION__;
//    std::vector<SGroup> aGroups = m_pOrm->selectGroupsAll();


//    QJsonArray jArray;
//    for(size_t i = 0; i < aGroups.size(); ++i)
//    {
//        QJsonValue jValue(aGroups[i].getJsonObject());
//        jArray.append(jValue);
//    }

//    QJsonDocument jDocument;
//    jDocument.setArray(jArray);
//    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    return aJson;
//}

QByteArray CServerLogic::getNewsAllVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    std::vector<CNews> aNews;
    if(bIsAbdmin)
    {
        aNews = m_pOrm->selectNewsAllVisibleByAdmin();
    }
    else
    {
        aNews = m_pOrm->selectNewsAllVisibleByUser(nWatcherUserId);
    }

    QJsonArray jArray;
    for(size_t i = 0; i < aNews.size(); ++i)
    {
        QJsonValue jValue(aNews[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

bool CServerLogic::addPlayer(QByteArray jPlayer)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = SPlayer::getObjectFromJson(jPlayer);
    if(Player.m_sName.empty())
    {
        return false;
    }
    m_pOrm->insertPlayer(Player);
    return true;
}

bool CServerLogic::updatePlayer(QByteArray jPlayer)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = SPlayer::getObjectFromJson(jPlayer);
    if(Player.m_nId)
    {
        m_pOrm->updatePlayer(Player);
        return true;
    }
    return false;
}

bool CServerLogic::updatePlayerCredential(QByteArray jCredential)
{
    qDebug() << __FUNCTION__;
    SCredential Credential = SCredential::getObjectFromJson(jCredential);
    if(Credential.m_nId)
    {
        m_pOrm->updateCredential(Credential);
        return true;
    }
    return false;
}

bool CServerLogic::deletePlayer(int nPlayerId)
{
    //    m_pOrm->insertUser(User);
        return false;
}

bool CServerLogic::addUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;
    SUser User = SUser::getObjectFromJson(jUser);
    if(User.m_sName.empty())
    {
        return false;
    }
    SUserStat UserStat(5, 5, 10, 900, 0);
    m_pOrm->insertUser(User, UserStat);
    return true;
}

bool CServerLogic::updateUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;

    SUser User = SUser::getObjectFromJson(jUser);
    if(User.m_nId)
    {
        m_pOrm->updateUser(User);
        return true;
    }
    return false;
}

bool CServerLogic::deleteUser(int nUserId)
{
//    m_pOrm->insertUser(User);
    return false;
}

QByteArray CServerLogic::genereateNewHashForUserByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    std::string sNewHash = m_pOrm->createUniqueHash();

    m_pOrm->setHashStringToUser(sNewHash, nWatcherUserId);

    return QByteArray(("{\"value\": \"" + sNewHash + "\"}").c_str());
}

QByteArray CServerLogic::useItemByHashByPlayerId(std::string sHash, int nPlayerId)
{
    /// TODO add some skills checks here

    QByteArray Result = getActionsByHash(sHash);
    if(Result.isEmpty())
    {
        return Result;
    }

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    m_pOrm->setActionHashStringToUser(sHash, nWatcherUserId);

    return Result;
}

QByteArray CServerLogic::getActionsByHash(std::string sHash)
{
    qDebug() << __FUNCTION__;

    SUser User = m_pOrm->findUserByHashString(sHash);
    if(User.m_nId > 0)
    {
        qDebug() << "user found";
        return QByteArray(("{\"object\": \"" + User.m_sSurname
                           + " "  + User.m_sName
                           + " "  + User.m_sPatronymic
                          + "\", \"data\": \"Человек\", \"actions\": [\"Взять анализ крови\", \"Оглушить\"]}").c_str());
    }

    SItem Item = m_pOrm->findItemByHashString(sHash);
    if(Item.m_nId > 0)
    {
        qDebug() << "item found";
        IItem* pItem = CItemManager::parseItem(Item);
        if(pItem == 0)
        {
            qDebug() << "got 0 pointer from parser";
            return QByteArray();
        }
        return QByteArray(("{\"object\": \"" + pItem->getName()
                           + "\", \"data\": \"" + pItem->getType()
                           + "\", \"actions\": " + stringListToString(pItem->getActions()) + "}").toUtf8());
    }
    qDebug() << "nothing found";
    return QByteArray();
}

QByteArray CServerLogic::actionByPlayerId(std::string sAction, int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    std::string sTargetHash = m_pOrm->getActionHashStringFromUser(nWatcherUserId);

    SUser TargetUser = m_pOrm->findUserByHashString(sTargetHash);
    if(TargetUser.m_nId > 0)
    {
        qDebug() << "user found";
        if(sAction == "Оглушить")
        {
            m_pOrm->stunUserId(DEFAULT_STUN_SEC, TargetUser.m_nId);
            int nTargetPlayerId = getPlayerIdByUserId(TargetUser.m_nId);
            if(nTargetPlayerId > 0)
            {
                emit statusChange("Оглушен", nTargetPlayerId);
            }
            return QByteArray("qr action accepted:");
        }
    }

    SItem Item = m_pOrm->findItemByHashString(sTargetHash);
    if(Item.m_nId > 0)
    {
        qDebug() << "item found";
        IItem* pItem = CItemManager::parseItem(Item);
        if(pItem == 0)
        {
            qDebug() << "got 0 pointer from parser";
            return QByteArray("internal error:");
        }
        if(pItem->eType == HealShot)
        {
            int nTargetPlayerId = getPlayerIdByUserId(nWatcherUserId);
            if(sAction == USE_HEALSHOT)
            {
                EUserStates eState = m_pOrm->modifyHealthUserId(1, nWatcherUserId);
                if(eState == AlreadyDead)
                {
                    emit statusChange("На Вас применено лекарство, однако, Вы уже мертвы и лекарство не помогает", nTargetPlayerId);
                }
                else if(eState == Healed)
                {
                    emit statusChange("На Вас применено лекарство, часть Вашего здоровья восстановлена", nTargetPlayerId);
                }
                else if(eState == HealedToCap)
                {
                    emit statusChange("На Вас применено лекарство, Вы более не ранены", nTargetPlayerId);
                }
                else if(eState == AlreadyFull)
                {
                    emit statusChange("На Вас применено лекарство, однако, Вы и так были здоровы", nTargetPlayerId);
                }
                emit qrClosed(nPlayerId);
                return QByteArray("qr action accepted:");
            }
        }
        if(pItem->eType == Airlock)
        {
            int nTargetPlayerId = getPlayerIdByUserId(nWatcherUserId);
            if(sAction == USE_AIRLOCK)
            {
                bool bIsOutside = m_pOrm->switchAirType(DEFAULT_AIR_SEC, nWatcherUserId);
                if(bIsOutside){
                    emit statusChange("Вы вышли со станции", nTargetPlayerId);
                }
                else
                {
                    emit statusChange("Вы вошли на станцию", nTargetPlayerId);
                }
                emit qrClosed(nPlayerId);
                return QByteArray("qr action accepted:");
            }
        }
        return QByteArray(("{\"object\": \"" + pItem->getName()
                           + "\", \"data\": \"" + pItem->getType()
                           + "\", \"actions\": " + stringListToString(pItem->getActions()) + "}").toUtf8());
    }
    return QByteArray("target not found:");
}

void CServerLogic::healthLossByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    EUserStates eState = m_pOrm->modifyHealthUserId(-1, nWatcherUserId);
    if(eState == AlreadyDead)
    {
        emit statusChange("Вы уже мертвы, Вы не можете стать ещё мертвее", nPlayerId);
    }
    else if(eState == Died)
    {
        emit statusChange("Вы погибли!", nPlayerId);
    }
    else if(eState == Damaged)
    {
        emit statusChange("Вы ранены!", nPlayerId);
    }
}
void CServerLogic::psyLossByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    m_pOrm->modifyPsyUserId(-5, nWatcherUserId);
    emit statusChange("Ваша психика стала менее устойчива", nPlayerId);
}

//QByteArray CServerLogic::getJsonFromUser(SUser &User)
//{
//    QJsonObject jUser;
//    jUser.insert("Id", User.m_nId);
//    jUser.insert("Name", User.m_sName.c_str());
//    jUser.insert("Surname", User.m_sSurname.c_str());
//    jUser.insert("Patronymic", User.m_sPatronymic.c_str());
//    jUser.insert("BirthDate", User.m_sBirthDate.c_str());
//    jUser.insert("Profession", User.m_sProfession.c_str());
//    jUser.insert("Description", User.m_sDescription.c_str());

//    QJsonDocument jDocument;
//    jDocument.setObject(jUser);
//    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    return aJson;
//}

