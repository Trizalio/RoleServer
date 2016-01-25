#include "cserverlogic.h"

CServerLogic::CServerLogic(CSqlConnector *pSqlConnector):
    m_Orm(pSqlConnector)
{

}

int CServerLogic::login(std::string sLogin, std::string sPassword)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_Orm.findPlayerByLoginAndPassHash(sLogin, sPassword);
    return Player.m_nId;
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

QByteArray CServerLogic::getUserData(int nId)
{
    qDebug() << __FUNCTION__;
    CUser User = m_Orm.getUserInfoById(nId);

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

//    return getJsonFromUser(User);
    return User.getJson();
}

QByteArray CServerLogic::getPeopleData()
{
    qDebug() << __FUNCTION__;
    std::vector<SUser> Users = m_Orm.selectUserAll();


    QJsonArray jMapArray;

    for(size_t i = 0; i < Users.size(); ++i)
    {

        QJsonValue jRowValue(QString(getJsonFromUser(Users[i])));
        jMapArray.append(jRowValue);
    }

//    QJsonValue jMapValue(jMapArray);
//    QJsonValue jWidthValue(pMap.getWidth());
//    QJsonValue jHeightValue(pMap.getHeight());

//    QJsonObject jMainObject;
//    jMainObject.insert("Map", jMapValue);
//    jMainObject.insert("Width", jWidthValue);
//    jMainObject.insert("Height", jHeightValue);

    QJsonDocument jDocument;
    jDocument.setArray(jMapArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    QByteArray aJson;
    return aJson;
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

