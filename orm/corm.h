#ifndef CORM_H
#define CORM_H

#include "orm/csqlconnector.h"
#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/splayer.h"
#include "orm/sql_objects/scredential.h"
#include "orm/sql_objects/smessage.h"
#include "orm/sql_objects/sgroup.h"
#include "orm/sql_objects/srole.h"
#include "orm/aggregation_objects/sdialogue.h"
#include "orm/aggregation_objects/cuser.h"
#include "orm/aggregation_objects/cgroup.h"

#define DATABASE_UTF8_SCRIPT std::string("ALTER DATABASE ") + DATABASE_NAME + std::string(" CHARACTER SET utf8 COLLATE utf8_general_ci")

class COrm
{
public:
    COrm(CSqlConnector* pSqlConnector);

    void insertUser(SUser& User);
    void insertPlayer(SPlayer& Player);
    void insertCredential(SCredential& Credential);
    void insertMessage(SMessage& Message);
    void insertGroup(SGroup& Group);
    void insertRole(SRole& Role);

    SUser findUserById(int nId);
    SPlayer findPlayerById(int nId);
    SGroup findGroupById(int nId);
    std::vector<SRole> findRolesByUserId(int nUserId);
    std::vector<SRole> findRolesByGroupId(int nGroupId);
//    void



    SPlayer findPlayerByLoginAndPassHash(std::string sLogin, std::string sPasswordHash);

    ///////////////////////////
    /// aggregation objects ///
    ///////////////////////////

    std::vector<SDialogue> selectUserDialogues();
    CUser getUserInfoById(int nId, int nWatcherId);
    CGroup getGroupInfoByIdByWatcher(int nId, int nWatcherId);
    CGroup getGroupInfoById(int nId);

    /////////////
    /// other ///
    /////////////

    std::vector<SGroup> selectAllGroupsVisibleByUser(int nId);

    ////////////
    /// junk ///
    ////////////

    std::vector<CGroup> selectAllGroupsInfoVisibleByUser(int nId);
    std::vector<SGroup> selectGroupsAll();
    std::vector<SUser> selectUserAll();
    SPlayer selectPlayerBy(std::string sName, std::string sSurname, std::string sPatronymic,
                           std::string sNick, std::string sBirthDate, std::string sQuenta);


private:
    void disableForingKeys();
    void enableForingKeys();

    void dropTables();
    void createTables();


    CSqlConnector* m_pCSqlConnector;
};

#endif // CORM_H
