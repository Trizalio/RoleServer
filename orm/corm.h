#ifndef CORM_H
#define CORM_H

#include "orm/csqlconnector.h"
#include "orm/sql_objects/suser.h"

class COrm
{
public:
    COrm(CSqlConnector* pSqlConnector);

    void insertUser(SUser& User);
    std::vector<SUser> selectUserAll();
private:
    void dropTables();
    void createTables();


    CSqlConnector* m_pCSqlConnector;
};

#endif // CORM_H
