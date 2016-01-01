#include "corm.h"

COrm::COrm(CSqlConnector *pSqlConnector):
    m_pCSqlConnector(pSqlConnector)
{
    dropTables();
    createTables();
    SUser test("test_name","test_surname","test_patronymic","3015-11-12","test_profession","test_description");
    insertUser(test);
    std::vector<SUser> res = selectUserAll();
    for(int i = 0; i < res.size(); ++i)
    {
        qDebug() << res.at(i).m_nId;
        qDebug() << res.at(i).m_nId << res.at(i).m_sName.c_str() << res.at(i).m_sSurname.c_str() <<
                    res.at(i).m_sPatronymic.c_str() << res.at(i).m_sBirthDate.c_str() <<
                    res.at(i).m_sProfession.c_str() << res.at(i).m_sDescription.c_str();
    }
}

void COrm::insertUser(SUser& User)
{
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Users` \
(`name`,`surname`,`patronymic`,`birth_date`,`profession`,`description`) VALUES \
(?,?,?,?,?,?);");
    pPreparedStatement->setString(1, User.m_sName);
    pPreparedStatement->setString(2, User.m_sSurname);
    pPreparedStatement->setString(3, User.m_sPatronymic);
    pPreparedStatement->setString(4, User.m_sBirthDate);
    pPreparedStatement->setString(5, User.m_sProfession);
    pPreparedStatement->setString(6, User.m_sDescription);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

std::vector<SUser> COrm::selectUserAll()
{
    std::vector<SUser> Result;
    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("SELECT * FROM Users;");
    while (pResult->next()) {
        Result.push_back(SUser(pResult->getInt("id"),
        pResult->getString("name").c_str(),
        pResult->getString("surname").c_str(),
        pResult->getString("patronymic").c_str(),
        pResult->getString("birth_date").c_str(),
        pResult->getString("profession").c_str(),
        pResult->getString("description").c_str()));
    }
    delete pResult;
    return Result;
}

void COrm::dropTables()
{
    m_pCSqlConnector->execute("DROP TABLE IF EXISTS `Users`;");
}

void COrm::createTables()
{
    m_pCSqlConnector->execute("CREATE TABLE `Users` (\
                `id` INTEGER NOT NULL AUTO_INCREMENT,\
                `name` VARCHAR(50) NOT NULL,\
                `surname` VARCHAR(50) NOT NULL,\
                `patronymic` VARCHAR(50) NOT NULL,\
                `birth_date` DATE NOT NULL,\
                `profession` VARCHAR(50) NOT NULL,\
                `description` MEDIUMTEXT NOT NULL,\
                PRIMARY KEY (`id`)\
              );");
}
