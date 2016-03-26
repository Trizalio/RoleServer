#ifndef CSERVERLOGIC_H
#define CSERVERLOGIC_H

#include <iostream>
#include <stdio.h>

#include <orm/corm.h>

class CServerLogic
{
public:
    CServerLogic(CSqlConnector* pSqlConnector);

    SPlayer login(std::string sLogin, std::string sPassword);
    SPlayer getPlayerById(int nId);
    QByteArray getPlayerData(int nId);
    QByteArray getPlayersAll(); /// Admin

    QByteArray getUserDataByWatcher(int nId, int nWatcherId);
    QByteArray getUsersAllData();

    QByteArray getProjectDataByWatcher(int nId, int nWatcherId);
    QByteArray getProjectsDataByWatcher(int nId);
    QByteArray getProjectsAllData(); /// Unused

    QByteArray getNewsAllByWatcher(int nId);

    bool addPlayer(QByteArray jPlayer);
    bool updatePlayer(QByteArray jPlayer);
    bool deletePlayer(int nPlayerId);

    bool addUser(QByteArray jUser);
    bool updateUser(QByteArray jUser);
    bool deleteUser(int nUserId);

private:
    QByteArray getJsonFromUser(SUser& User);

    COrm m_Orm;
};

#endif // CSERVERLOGIC_H
