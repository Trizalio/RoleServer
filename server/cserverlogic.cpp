#include "cserverlogic.h"

CServerLogic::CServerLogic(CSqlConnector *pSqlConnector):
    m_Orm(pSqlConnector)
{

}

SPlayer CServerLogic::login(std::string sLogin, std::string sPassword)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_Orm.findPlayerByLoginAndPassHash(sLogin, sPassword);
    return Player;
}

QByteArray CServerLogic::getPlayerData(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_Orm.findPlayerById(nId);

    QJsonObject jPlayer;
    jPlayer.insert("Id", Player.m_nId);
    jPlayer.insert("UserId", Player.m_nUserId);
    jPlayer.insert("Name", Player.m_sName.c_str());
    jPlayer.insert("Surname", Player.m_sSurname.c_str());
    jPlayer.insert("Patronymic", Player.m_sPatronymic.c_str());
    jPlayer.insert("Nick", Player.m_sNick.c_str());
    jPlayer.insert("BirthDate", Player.m_sBirthDate.c_str());
    jPlayer.insert("Quenta", Player.m_sQuenta.c_str());

    QJsonDocument jDocument;
    jDocument.setObject(jPlayer);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

QByteArray CServerLogic::getUserDataByWatcher(int nId, int nWatcherId)
{
    qDebug() << __FUNCTION__;
    CUser User = m_Orm.getUserInfoById(nId, nWatcherId);
    return User.getJson();
}

QByteArray CServerLogic::getUsersAllData()
{
    qDebug() << __FUNCTION__;
    std::vector<SUser> Users = m_Orm.selectUserAll();

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
    CGroup Group = m_Orm.getGroupInfoByIdByWatcher(nId, nWatcherId);
    return Group.getJson();
}

QByteArray CServerLogic::getProjectsDataByWatcher(int nId)
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> aGroups = m_Orm.selectAllGroupsVisibleByUser(nId);
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
    std::vector<SGroup> aGroups = m_Orm.selectGroupsAll();


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
    std::vector<CNews> aNews = m_Orm.selectNewsAllVisibleByUser(nId);

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

bool CServerLogic::addUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;
    SUser User = SUser::getObjectFromJson(jUser);
    m_Orm.insertUser(User);
    return true;
}

bool CServerLogic::updateUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;
    SUser User = SUser::getObjectFromJson(jUser);
    if(User.m_nId)
    {
        m_Orm.updateUser(User);
        return true;
    }
    return false;
}

bool CServerLogic::deleteUser(int nUserId)
{
//    m_Orm.insertUser(User);
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

