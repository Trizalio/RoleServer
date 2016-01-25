#include "corm.h"

COrm::COrm(CSqlConnector *pSqlConnector):
    m_pCSqlConnector(pSqlConnector)
{
    // №Terra04C24
    dropTables();
    createTables();
    SUser User1("Олег","Пчёлкин","Борисович","2074-09-03",
               "Начальник терраформационной базы","Обращаться через секретаря");
    SUser User2("Лаврентий","Лютов","Тимурович","2064-12-05",
               "Личный секретарь начальника базы","Пожалуйста, составляйте обращения по протоколу, чётко и ясно. Не верно обормленные заявки рассматриваться не будут");
    SUser User3("Никифор","Данилов","Григорьевич","2061-08-10",
               "Начальник по техническому обеспечению","Пожалуйста, подавая заявки на получение образцов прикрепляйте план работ!");
    SUser User4("Ариадна","Лебедева","Вечеславовна","2077-06-07",
               "Главный программист","Рада помочь!");
    SPlayer Player1(1, "Парамон", "Щербаков", "Кириллович", "Mr. White",
                   "1974-08-11", "Квента начальника базы");
    SPlayer Player2(2, "Апполинарий", "Холодков", "Егорович", "Mr. Orange",
                   "1989-03-17", "Квента секретаря начальника базы");
    SPlayer Player3(3, "Никон", "Михайлов", "Святославович", "Mr. Red",
                   "1986-02-02", "Старый космический волк. Настоящий космический боцман. Знает каждую заклепку корабля, каждый шурупчик на станции. Поддерживать эти объекты в рабочем состоянии - его непосредственная задача. Склады - это его вотчина, не расстается с планшетом, куда вносит каждую возможную неисправность. Параноик и перфекционист. С подчиненными строг, прекрасно знает, кто чем занят, а также кто, чем должен быть занят.");
    SPlayer Player4(4, "Аза", "Стручкова", "Александровна", "Ms. Orange",
                   "1973-01-16", "Если технический персонал, что-то собрал, то самое время найти программиста, чтобы аппарат ожил, замигал лампочками, зашевелился. И не спрашивайте, как этим управлять. Если вы в принципе способны что-то понять, вам все объяснят. Полный курс космической подготовки.");
    SCredential Credential1(1, "1", "1");
    SCredential Credential2(2, "2", "2");
    SCredential Credential3(3, "3", "3");
    SCredential Credential4(4, "4", "4");
    SGroup Group1(0, "Управление базы", "Принимает наиболее важные решения в жизни базы", SGroup::LAB);
    SGroup Group2(1, "Отдел Технического обеспечения", "Обеспечивает нормальную работу техноческой составляющей базы", SGroup::LAB);
    SRole Role1(1, 1, true);
    SRole Role2(2, 1, false);
    SRole Role3(3, 2, true);
    SRole Role4(4, 2, false);
    qDebug() << "insert";
    insertUser(User1);
    insertUser(User2);
    insertUser(User3);
    insertUser(User4);
    qDebug() << "User";
    insertPlayer(Player1);
    insertPlayer(Player2);
    insertPlayer(Player3);
    insertPlayer(Player4);
    qDebug() << "Player";
    insertCredential(Credential1);
    insertCredential(Credential2);
    insertCredential(Credential3);
    insertCredential(Credential4);
    qDebug() << "Credential";
    insertGroup(Group1);
    insertGroup(Group2);
    qDebug() << "Group";
    insertRole(Role1);
    insertRole(Role2);
    insertRole(Role3);
    insertRole(Role4);
    qDebug() << "Group";
    std::vector<SUser> res = selectUserAll();
    for(size_t i = 0; i < res.size(); ++i)
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

void COrm::insertPlayer(SPlayer &Player)
{
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Players` \
(`fk_Users_id`,`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`) VALUES \
(?,?,?,?,?,?,?);");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Player.m_nUserId);
    pPreparedStatement->setString(i++, Player.m_sName);
    pPreparedStatement->setString(i++, Player.m_sSurname);
    pPreparedStatement->setString(i++, Player.m_sPatronymic);
    pPreparedStatement->setString(i++, Player.m_sNick);
    pPreparedStatement->setString(i++, Player.m_sBirthDate);
    pPreparedStatement->setString(i++, Player.m_sQuenta);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertCredential(SCredential &Credential)
{
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Credentials` \
(`id`,`login`,`passwordHash`) VALUES \
(?,?,?);");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Credential.m_nId);
    pPreparedStatement->setString(i++, Credential.m_sLogin);
    pPreparedStatement->setString(i++, Credential.m_sPasswordHash);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertMessage(SMessage &Message)
{
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Messages` \
(`fk_Users_id_from`,`fk_Users_id_to`,`subject`,`text`,`anonymously`) VALUES \
(?, ?, ?, ?, ?);");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Message.m_nSenderId);
    pPreparedStatement->setInt(i++, Message.m_nRecieverId);
    pPreparedStatement->setString(i++, Message.m_sSubject);
    pPreparedStatement->setString(i++, Message.m_sText);
    pPreparedStatement->setBoolean(i++, Message.m_bAnonymously);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertGroup(SGroup &Group)
{
    sql::PreparedStatement* pPreparedStatement;
    unsigned short i = 1;
    if(Group.m_nParentId) {
        pPreparedStatement= m_pCSqlConnector->prepare("INSERT INTO `Groups` \
(`fk_Groups_id_parent`,`name`,`description`,`type`) VALUES \
(?, ?, ?, ?);");
        pPreparedStatement->setInt(i++, Group.m_nParentId);
    }
    else
    {
        pPreparedStatement= m_pCSqlConnector->prepare("INSERT INTO `Groups` \
(`name`,`description`,`type`) VALUES \
(?, ?, ?);");
    }
    pPreparedStatement->setString(i++, Group.m_sName);
    pPreparedStatement->setString(i++, Group.m_sDescription);
    if(Group.m_eType == SGroup::GROUP)
    {
        pPreparedStatement->setString(i++, "Group");
    }
    else if(Group.m_eType == SGroup::PROJECT)
    {
        pPreparedStatement->setString(i++, "Project");
    }
    else if(Group.m_eType == SGroup::TASK)
    {
        pPreparedStatement->setString(i++, "Task");
    }
    else if(Group.m_eType == SGroup::LAB)
    {
        pPreparedStatement->setString(i++, "Lab");
    }
    else
    {
        qDebug() << "ERROR:" << "Group type enums value";
        return;
    }
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertRole(SRole &Role)
{
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Roles` \
(`fk_Users_id`,`fk_Groups_id`,`owner`) VALUES \
(?, ?, ?);");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Role.m_nUserId);
    pPreparedStatement->setInt(i++, Role.m_nGroupId);
    pPreparedStatement->setInt(i++, (int)(Role.m_bOwner));
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

std::vector<SDialogue> COrm::selectUserDialogues()
{
    std::vector<SDialogue> aResult;

    return aResult;
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

CUser COrm::getUserInfoById(int nId)
{
    CUser User = CUser(findUserById(nId));
    std::vector<SRole> UserRoles = findRolesByUserId(nId);
    for(size_t i = 0; i < UserRoles.size(); ++i)
    {
        User.addGroup(findGroupById(UserRoles.at(i).m_nGroupId));
    }
    return User;
}

SUser COrm::findUserById(int nId)
{
    qDebug() << __FUNCTION__;
    SUser Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Users.id, \
Users.name, \
Users.surname, \
Users.patronymic, \
Users.birth_date, \
Users.profession, \
Users.description \
from Users \
where Users.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SUser(pResult->getInt("id"),
            pResult->getString("name").c_str(),
            pResult->getString("surname").c_str(),
            pResult->getString("patronymic").c_str(),
            pResult->getString("birth_date").c_str(),
            pResult->getString("profession").c_str(),
            pResult->getString("description").c_str());
    }
    delete pResult;
    return Result;
}

SPlayer COrm::findPlayerByLoginAndPassHash(std::string sLogin, std::string sPasswordHash)
{
    qDebug() << __FUNCTION__;
    SPlayer Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Players.id, \
Players.fk_Users_id, \
Players.name, \
Players.surname, \
Players.patronymic, \
Players.nick, \
Players.birth_date, \
Players.quenta \
from Players \
join Credentials \
on Players.id = Credentials.id \
where Credentials.login = ? \
and Credentials.passwordHash = ?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, sLogin);
    pPreparedStatement->setString(i++, sPasswordHash);
    qDebug() << sLogin.c_str() <<sPasswordHash.c_str();
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SPlayer(pResult->getInt("id"),
            pResult->getInt("fk_Users_id"),
            pResult->getString("name").c_str(),
            pResult->getString("surname").c_str(),
            pResult->getString("patronymic").c_str(),
            pResult->getString("nick").c_str(),
            pResult->getString("birth_date").c_str(),
            pResult->getString("quenta").c_str());
    }
    delete pResult;
    return Result;
}

SPlayer COrm::findPlayerById(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Players.id, \
Players.fk_Users_id, \
Players.name, \
Players.surname, \
Players.patronymic, \
Players.nick, \
Players.birth_date, \
Players.quenta \
from Players \
where Players.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SPlayer(pResult->getInt("id"),
            pResult->getInt("fk_Users_id"),
            pResult->getString("name").c_str(),
            pResult->getString("surname").c_str(),
            pResult->getString("patronymic").c_str(),
            pResult->getString("nick").c_str(),
            pResult->getString("birth_date").c_str(),
            pResult->getString("quenta").c_str());
    }
    delete pResult;
    return Result;
}

SGroup COrm::findGroupById(int nId)
{
    qDebug() << __FUNCTION__;
    SGroup Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Groups.id, \
Groups.fk_Groups_id_parent, \
Groups.name, \
Groups.description, \
Groups.type \
from Groups \
where Groups.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SGroup(pResult->getInt("id"),
            pResult->getInt("fk_Groups_id_parent"),
            pResult->getString("name").c_str(),
            pResult->getString("description").c_str(),
            pResult->getString("type").c_str());
    }
    delete pResult;
    return Result;
}

std::vector<SRole> COrm::findRolesByUserId(int nUserId)
{
    qDebug() << __FUNCTION__;
    std::vector<SRole> Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select id, \
fk_Users_id, \
fk_Groups_id, \
owner \
from Roles \
where fk_Users_id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nUserId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(SRole(pResult->getInt("id"),
            pResult->getInt("fk_Users_id"),
            pResult->getInt("fk_Groups_id"),
            (bool)(pResult->getInt("owner"))));
    }
    delete pResult;
    return Result;
}

SPlayer COrm::selectPlayerBy(std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta)
{
    SPlayer Result;
//    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("SELECT * FROM Users;");
//    while (pResult->next()) {
//        Result.push_back(SUser(pResult->getInt("id"),
//        pResult->getString("name").c_str(),
//        pResult->getString("surname").c_str(),
//        pResult->getString("patronymic").c_str(),
//        pResult->getString("birth_date").c_str(),
//        pResult->getString("profession").c_str(),
//        pResult->getString("description").c_str()));
//    }
//    delete pResult;
    return Result;
}

void COrm::disableForingKeys()
{
    m_pCSqlConnector->execute("SET FOREIGN_KEY_CHECKS=0;");
}

void COrm::enableForingKeys()
{
    m_pCSqlConnector->execute("SET FOREIGN_KEY_CHECKS=1;");
}

void COrm::dropTables()
{
    disableForingKeys();
    m_pCSqlConnector->execute(USER_DROP_SCRIPT);
    m_pCSqlConnector->execute(PLAYER_DROP_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_DROP_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_DROP_SCRIPT);
    m_pCSqlConnector->execute(GROUP_DROP_SCRIPT);
    m_pCSqlConnector->execute(ROLE_DROP_SCRIPT);
}

void COrm::createTables()
{
    m_pCSqlConnector->execute(DATABASE_UTF8_SCRIPT);

    m_pCSqlConnector->execute(USER_CREATE_SCRIPT);
    m_pCSqlConnector->execute(PLAYER_CREATE_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_CREATE_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_CREATE_SCRIPT);
    m_pCSqlConnector->execute(GROUP_CREATE_SCRIPT);
    m_pCSqlConnector->execute(ROLE_CREATE_SCRIPT);

    m_pCSqlConnector->execute(PLAYER_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_CONNECT_SCRIPT_1);
    m_pCSqlConnector->execute(MESSAGE_CONNECT_SCRIPT_2);
    m_pCSqlConnector->execute(GROUP_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(ROLE_CONNECT_SCRIPT_1);
    m_pCSqlConnector->execute(ROLE_CONNECT_SCRIPT_2);

    m_pCSqlConnector->execute(USER_UTF8_SCRIPT);
    m_pCSqlConnector->execute(PLAYER_UTF8_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_UTF8_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_UTF8_SCRIPT);
    m_pCSqlConnector->execute(GROUP_UTF8_SCRIPT);
    m_pCSqlConnector->execute(ROLE_UTF8_SCRIPT);
    /// keys
    enableForingKeys();
}
