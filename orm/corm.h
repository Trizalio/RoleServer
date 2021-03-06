#ifndef CORM_H
#define CORM_H

#include <QDateTime>
#include <QCryptographicHash>

#include "orm/csqlconnector.h"
//#include "orm/sql_objects/shash.h"
#include "orm/sql_objects/sitem.h"
#include "orm/sql_objects/slore.h"
#include "orm/sql_objects/suserstat.h"
#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/splayer.h"
#include "orm/sql_objects/scredential.h"
#include "orm/sql_objects/smessage.h"
#include "orm/sql_objects/sgroup.h"
#include "orm/sql_objects/srole.h"
#include "orm/sql_objects/snews.h"
#include "orm/aggregation_objects/sdialogue.h"
#include "orm/aggregation_objects/cuser.h"
#include "orm/aggregation_objects/cgroup.h"
#include "orm/aggregation_objects/cnews.h"




#define HASH_LEN 4

#define DATABASE_UTF8_SCRIPT QString("ALTER DATABASE ") + DATABASE_NAME + QString(" CHARACTER SET utf8 COLLATE utf8_general_ci")

class COrm
{
public:
    COrm(CSqlConnector* pSqlConnector);

//    void insertHash(SHash& Hash);
    void insertUser(SUser User, SUserStat& UserStat);
    void insertPlayer(SPlayer Player);
    void insertCredential(SCredential Credential);
    void insertMessage(SMessage& Message);
    void insertGroup(SGroup& Group);
    void insertRole(SRole Role);
    void insertNews(SNews& News);
    QString insertItem(SItem Item);
    void insertLore(SLore Lore);

    void updateUser(SUser& User);
    void updateUserStat(SUserStat& UserStat);
    void updatePlayer(SPlayer& Player);
    void updateCredential(SCredential& Credential);

    void deleteHash(int& nHashId);
    void deleteUser(int& nUserId);
    void deletePlayer(int& nPlayerId);
    void deleteCredential(int& nCredentialId);
//    void deleteMessage(int& nMessageId);
    void deleteGroup(int& nGroupId);
    void deleteRole(int& nRoleId);
    void deleteNews(int& nNewsId);

    /////////////////////
    /// Basic objects ///
    /////////////////////

    SUser findUserById(int nId);
    SUserStat findUserStatsById(int nId);
    SPlayer findPlayerById(int nId);
    SPlayer findPlayerByUserId(int nUserId);
    SGroup findGroupById(int nId);
    std::vector<SRole> findRolesByUserId(int nUserId);
    std::vector<SRole> findRolesByGroupId(int nGroupId);
    SItem findItemById(int nId);
    SPlayer findPlayerByLoginAndPassHash(QString sLogin, QString sPasswordHash);

    std::vector<SLore> getAllLores();

    ///////////////////////////
    /// Aggregation objects ///
    ///////////////////////////

    std::vector<SDialogue> selectUserDialogues(); /// Unused

    CUser getUserByIdVisibleByAdmin(int nId);
    CUser getUserByIdVisibleByUser(int nId, int nWatcherUserId);

    CGroup getGroupInfoByIdVisibleByAdmin(int nId);
    CGroup getGroupInfoByIdVisibleByUser(int nId, int nWatcherUserId);

    std::vector<CNews> selectNewsAllVisibleByAdmin();
    std::vector<CNews> selectNewsAllVisibleByUser(int nWatcherId);
    std::vector<CNews> selectNewsByGroup(int nGroupId);

    /////////////
    /// Other ///
    /////////////

    std::vector<SGroup> selectAllGroupsVisibleByAdmin();
    std::vector<SGroup> selectAllGroupsVisibleByUser(int nId);

    ////////////////
    /// buisness ///
    ////////////////

    void stunUserId(int nStun, int nUserId);
    bool switchAirType(int nInitAirSeconds, int nUserId);

    EUserStates modifyAirUserId(int nDelta, int nUserId);
    EUserStates modifyHealthUserId(int nDelta, int nUserId);
    void modifyPsyUserId(int nDelta, int nUserId);

    std::vector<SUserStat> selectUserStatsAll();

    ////////////
    /// Hash ///
    ////////////

//    SHash findHashByHashString(QString sHash);
    SUser findUserByHashString(QString sHash);
    SItem findItemByHashString(QString sHash);
//    SUser findUserByHash(SHash Hash);
    QString createUniqueHash();

    void setHashStringToUser(QString sHash, int nUserId);
    void setActionHashStringToUser(QString sHash, int nUserId);

    QString getActionHashStringFromUser(int nUserId);

    ////////////
    /// Junk ///
    ////////////

//    std::vector<CGroup> selectAllGroupsInfoVisibleByUser(int nId);
    std::vector<SGroup> selectGroupsAll();
    std::vector<SUser> selectUserAll(); /// Used
    std::vector<SPlayer> selectPlayersAll(); /// Used
    SPlayer selectPlayerBy(QString sName, QString sSurname, QString sPatronymic,
                           QString sNick, QString sBirthDate, QString sQuenta);


private:
    void disableForingKeys();
    void enableForingKeys();

    void dropTables();
    void createTables();

    CUser getUserById(int nId);
    CGroup getGroupInfoById(int nId);
    std::vector<CNews> selectNewsAll();

    CSqlConnector* m_pCSqlConnector;
};

#endif // CORM_H
