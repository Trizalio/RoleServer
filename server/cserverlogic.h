#ifndef CSERVERLOGIC_H
#define CSERVERLOGIC_H

#include <iostream>
#include <stdio.h>

#include <orm/corm.h>

class CServerLogic
{
public:
    CServerLogic(CSqlConnector* pSqlConnector);

    int login(std::string sLogin, std::string sPassword);
    QByteArray getPlayerData(int nId);

    QByteArray getUserDataByWatcher(int nId, int nWatcherId);
    QByteArray getUsersAllData();

    QByteArray getProjectDataByWatcher(int nId, int nWatcherId);
    QByteArray getProjectsDataByWatcher(int nId);
    QByteArray getProjectsAllData();

    QByteArray getNewsAllByWatcher(int nId);

private:
    QByteArray getJsonFromUser(SUser& User);

    COrm m_Orm;
};

#endif // CSERVERLOGIC_H