#ifndef CSERVERLOGIC_H
#define CSERVERLOGIC_H

#include <iostream>
#include <stdio.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <orm/corm.h>

class CServerLogic
{
public:
    CServerLogic(CSqlConnector* pSqlConnector);

    int login(std::string sLogin, std::string sPassword);
    QByteArray getPlayerData(int nId);
    QByteArray getUserData(int nId);
    QByteArray getPeopleData();

private:
    QByteArray getJsonFromUser(SUser& User);

    COrm m_Orm;
};

#endif // CSERVERLOGIC_H
