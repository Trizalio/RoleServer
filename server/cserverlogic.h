#ifndef CSERVERLOGIC_H
#define CSERVERLOGIC_H

#include <iostream>
#include <stdio.h>

#include "orm/corm.h"
#include "common/common.h"
#include "items/citemmanager.h"

class CServerLogic : public QObject
{
    Q_OBJECT

signals:
    void statusChange(QByteArray sStatusChange, int nPlayerId);
    void qrClosed(int nPlayerId);

public:
    CServerLogic(COrm *pOrm);

    /// Depricated
//    SPlayer login(QString sLogin, QString sPassword);
    QPair<int, bool> login(QString sLogin, QString sPassword);

    /// Depricated
//    SPlayer getPlayerById(int nId);

    bool CheckAdminByPlayerId(int nId);
    QPair<int, bool> getUserIdAndIsAdminByPlayerId(int nPlayerId);
    int getPlayerIdByUserId(int nUserId);

    QByteArray getPlayerData(int nPlayerId);                                    /// Self or Admin
    QByteArray getPlayersAll();                                                 /// Admin

    QByteArray getUserByIdVisibleByPlayerId(int nUserId, int nPlayerId);        /// Admin check inside
    QByteArray getUsersAllData();                                               /// Public

    QByteArray getUserStatusVisibleByPlayerId(int nPlayerId);

    QByteArray getProjectByIdVisibleByPlayerId(int nProjectId, int nPlayerId);  /// Admin check inside
    QByteArray getProjectsAllVisibleByPlayerId(int nPlayerId);                  /// Admin check inside
//    QByteArray getProjectsAllData();                                            /// Unused

    QByteArray getNewsAllVisibleByPlayerId(int nPlayerId);                      /// Admin check inside

    bool addPlayer(QByteArray jPlayer);                                         /// Admin
    bool updatePlayer(QByteArray jPlayer);                                      /// Admin
    bool updatePlayerCredential(QByteArray jCredential);                        /// Admin
    bool deletePlayer(int nPlayerId);                                           /// Admin

    bool addUser(QByteArray jUser);                                             /// Admin
    bool updateUser(QByteArray jUser);                                          /// Admin
    bool deleteUser(int nUserId);                                               /// Admin

    QByteArray genereateNewHashForUserByPlayerId(int nPlayerId);

    QByteArray useItemByHashByPlayerId(QString sHash, int nPlayerId);
    QByteArray getActionsByHash(QString sHash);
    QByteArray actionByPlayerId(QString sAction, int nPlayerId);

    void healthLossByPlayerId(int nPlayerId);
    void psyLossByPlayerId(int nPlayerId);

    QByteArray getLore();

    /// TODO ???
//    QByteArray getActions(QString sHash);

private:
//    QByteArray getJsonFromUser(SUser& User);

    int m_nHashsGenerated = 0;

    COrm* m_pOrm;
};

#endif // CSERVERLOGIC_H
