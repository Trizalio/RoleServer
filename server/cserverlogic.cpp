#include "cserverlogic.h"

CServerLogic::CServerLogic(COrm *pOrm):
    m_pOrm(pOrm)
{

}

SPlayer CServerLogic::login(std::string sLogin, std::string sPassword)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerByLoginAndPassHash(sLogin, sPassword);
    return Player;
}

SPlayer CServerLogic::getPlayerById(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nId);

    return Player;
}

QByteArray CServerLogic::getPlayerData(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nId);

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

QByteArray CServerLogic::getUserDataByWatcher(int nId, int nWatcherId)
{
    qDebug() << __FUNCTION__;
    CUser User = m_pOrm->getUserInfoById(nId, nWatcherId);
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

QByteArray CServerLogic::getProjectDataByWatcher(int nId, int nWatcherId)
{
    qDebug() << __FUNCTION__;
    CGroup Group = m_pOrm->getGroupInfoByIdByWatcher(nId, nWatcherId);
    return Group.getJson();
}

QByteArray CServerLogic::getProjectsDataByWatcher(int nId)
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> aGroups = m_pOrm->selectAllGroupsVisibleByUser(nId);
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
/// TODO merge methods
QByteArray CServerLogic::getProjectsAllData()
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> aGroups = m_pOrm->selectGroupsAll();


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

QByteArray CServerLogic::getNewsAllByWatcher(int nId)
{
    qDebug() << __FUNCTION__;
    std::vector<CNews> aNews = m_pOrm->selectNewsAllVisibleByUser(nId);

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
    m_pOrm->insertUser(User);
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

QByteArray CServerLogic::getJsonFromUser(SUser &User)
{
    QJsonObject jUser;
    jUser.insert("Id", User.m_nId);
    jUser.insert("Name", User.m_sName.c_str());
    jUser.insert("Surname", User.m_sSurname.c_str());
    jUser.insert("Patronymic", User.m_sPatronymic.c_str());
    jUser.insert("BirthDate", User.m_sBirthDate.c_str());
    jUser.insert("Profession", User.m_sProfession.c_str());
    jUser.insert("Description", User.m_sDescription.c_str());

    QJsonDocument jDocument;
    jDocument.setObject(jUser);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

