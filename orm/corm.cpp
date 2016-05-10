#include "corm.h"

COrm::COrm(CSqlConnector *pSqlConnector):
    m_pCSqlConnector(pSqlConnector)
{
    // №Terra04C24
    dropTables();
    createTables();
    SUser User2("Олег","Пчёлкин","Борисович", MALE,"2074-09-03",
               "Менеджмент","Начальник терраформационной базы","Обращаться через секретаря");
    SUser User3("Лаврентий","Лютов","Тимурович", MALE,"2064-12-05",
               "Работа с бумагами","Личный секретарь начальника базы","Пожалуйста, составляйте обращения по протоколу, чётко и ясно. Не верно обормленные заявки рассматриваться не будут");
    SUser User4("Никифор","Данилов","Григорьевич", MALE,"2061-08-10",
               "Сохранение ресурсов","Начальник по техническому обеспечению","Пожалуйста, подавая заявки на получение образцов прикрепляйте план работ!");
    SUser User5("Ариадна","Лебедева","Вечеславовна", FEMALE,"2077-06-07",
               "Информационная безопасность","Главный программист","Рада помочь!");
    SUser User6("Ильин","Илья","Вадимович", MALE,"2070-10-13",
                "Разведка","Уборщик","По помытому не ходите!");
    SUserStat UserStat2(5, 5, 10, -1, 0);
    SUserStat UserStat3(5, 4, 30, -1, 0);
    SUserStat UserStat4(5, 3, 50, -1, 0);
    SUserStat UserStat5(5, 2, 70, -1, 0);
    SUserStat UserStat6(5, 1, 100, -1, 0);
    SPlayer Player1("Орлов", "Михаил", "Юрьевич", "Тризалио",
                   "1991-03-21", "Администратор", true);
    SPlayer Player2(1, "Парамон", "Щербаков", "Кириллович", "Mr. White",
                   "1974-08-11", "Квента начальника базы", false);
    SPlayer Player3(2, "Апполинарий", "Холодков", "Егорович", "Mr. Orange",
                   "1989-03-17", "Квента секретаря начальника базы", false);
    SPlayer Player4(3, "Никон", "Михайлов", "Святославович", "Mr. Red", "1986-02-02",
                    "Старый космический волк. Настоящий космический боцман. Знает каждую заклепку корабля, каждый шурупчик на станции. Поддерживать эти объекты в рабочем состоянии - его непосредственная задача. Склады - это его вотчина, не расстается с планшетом, куда вносит каждую возможную неисправность. Параноик и перфекционист. С подчиненными строг, прекрасно знает, кто чем занят, а также кто, чем должен быть занят.",
                    false);
    SPlayer Player5(4, "Аза", "Стручкова", "Александровна", "Ms. Orange", "1973-01-16",
                    "Если технический персонал что-то собрал, то самое время найти программиста, чтобы аппарат ожил, замигал лампочками, зашевелился. И не спрашивайте, как этим управлять. Если вы в принципе способны что-то понять, вам все объяснят. Полный курс космической подготовки.",
                    false);
    SCredential Credential1(1, "0", SCredential::getPassHash("0"));
    SCredential Credential2(2, "1", SCredential::getPassHash("1"));
    SCredential Credential3(3, "2", SCredential::getPassHash("2"));
    SCredential Credential4(4, "3", SCredential::getPassHash("3"));
    SCredential Credential5(5, "4", SCredential::getPassHash("4"));
    SGroup Group1(0, "Управление базы", "Принимает наиболее важные решения в жизни базы", SGroup::LAB);
    SGroup Group2(1, "Отдел Технического обеспечения", "Обеспечивает нормальную работу техноческой составляющей базы", SGroup::LAB);
    SGroup Group3(0, "Нарушение системы жизнеобесспечения", "Необходимо повредить регенератор кислорода, воды, контроллер давления или систему поглощения углекислого газа", SGroup::HIDDEN);
    SRole Role1(1, 1, true);
    SRole Role2(2, 1, false);
    SRole Role3(3, 2, true);
    SRole Role4(4, 2, false);
    SRole Role5(4, 3, true);
    SNews News1(1, "2105-02-13", "Поздравляю всех с началом работ на станции", "Я очень рад видеть здесь такое множество лучших умов человечества, сплочённых единой целью. Я не сомневаюсь, что мы справимся с нашей задачей и откроем для человечества эпоху терраформирования.", false, true);
    SNews News2(3, "2107-03-27", "Потеряшки", "Уважаемый коллега, забывший эротический журнал на ремонтной консоли в ангаре дронов, найдись! Твоя вещь находится у начальника технической службы. ", false, true);
    SNews News3(4, "2107-03-27", "Обмен", "Обменяю полное собрание сочинений Джорджа Мартина, 76 томов, 23 гигабайта. Комиксы и интерактивки не предлагать!", false, false);
    SNews News4(5, "2109-11-07", "Пора действовать", "Время уходит, каждый день снижает шанс нашей миссии. Поторопитсь.", true, true);
    qDebug() << "insert";
    insertUser(User2, UserStat2);
    insertUser(User3, UserStat3);
    insertUser(User4, UserStat4);
    insertUser(User5, UserStat5);
    insertUser(User6, UserStat6);
    qDebug() << "User";
    insertPlayer(Player1);
    insertPlayer(Player2);
    insertPlayer(Player3);
    insertPlayer(Player4);
    insertPlayer(Player5);
    qDebug() << "Player";
    insertCredential(Credential1);
    insertCredential(Credential2);
    insertCredential(Credential3);
    insertCredential(Credential4);
    insertCredential(Credential5);
    qDebug() << "Credential";
    insertGroup(Group1);
    insertGroup(Group2);
    insertGroup(Group3);
    qDebug() << "Group";
    insertRole(Role1);
    insertRole(Role2);
    insertRole(Role3);
    insertRole(Role4);
    insertRole(Role5);
    qDebug() << "News";
    insertNews(News1);
    insertNews(News2);
    insertNews(News3);
    insertNews(News4);
    qDebug() << "Fin";
//    selectNewsAllVisibleByUser(1);
    /*std::vector<SUser> res = selectUserAll();
    for(size_t i = 0; i < res.size(); ++i)
    {
        qDebug() << res.at(i).m_nId;
        qDebug() << res.at(i).m_nId << res.at(i).m_sName.c_str() << res.at(i).m_sSurname.c_str() <<
                    res.at(i).m_sPatronymic.c_str() << res.at(i).m_sBirthDate.c_str() <<
                    res.at(i).m_sProfession.c_str() << res.at(i).m_sDescription.c_str();
    }*/
}

//void COrm::insertHash(SHash &Hash)
//{
//    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Hashs` \
//(`hash`) VALUES \
//(?);");
//    pPreparedStatement->setString(1, Hash.m_sHash);
//    pPreparedStatement->executeUpdate();
//    delete pPreparedStatement;
//}

void COrm::insertUser(SUser& User, SUserStat &UserStat)
{
    qDebug() << __FUNCTION__;
    unsigned short i = 1;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Users` \
(`name`,`surname`,`patronymic`,`male`,`birth_date`,`specialty`,`profession`,`description`) VALUES \
(?,?,?,?,?,?,?,?);");
    pPreparedStatement->setString(i++, User.m_sName);
    pPreparedStatement->setString(i++, User.m_sSurname);
    pPreparedStatement->setString(i++, User.m_sPatronymic);
    pPreparedStatement->setInt(i++, (int)User.m_bMale);
    pPreparedStatement->setString(i++, User.m_sBirthDate);
    pPreparedStatement->setString(i++, User.m_sSpecialty);
    pPreparedStatement->setString(i++, User.m_sProfession);
    pPreparedStatement->setString(i++, User.m_sDescription);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;

    qDebug() << __FUNCTION__ << 2;
    i = 1;
    if(UserStat.m_nAirId)
    {
        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `UserStats` \
(`id`,`hp_max`,`hp`,`pp`,`air`,`fk_Items_id_air`) VALUES \
(LAST_INSERT_ID(),?,?,?,?,?);");
        pPreparedStatement->setInt(i++, UserStat.m_nHpMax);
        pPreparedStatement->setInt(i++, UserStat.m_nHp);
        pPreparedStatement->setInt(i++, UserStat.m_nPp);
        pPreparedStatement->setInt(i++, UserStat.m_nAir);
        pPreparedStatement->setInt(i++, UserStat.m_nAirId);
    }
    else
    {
        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `UserStats` \
(`id`,`hp_max`,`hp`,`pp`,`air`) VALUES \
(LAST_INSERT_ID(),?,?,?,?);");
        pPreparedStatement->setInt(i++, UserStat.m_nHpMax);
        pPreparedStatement->setInt(i++, UserStat.m_nHp);
        pPreparedStatement->setInt(i++, UserStat.m_nPp);
        pPreparedStatement->setInt(i++, UserStat.m_nAir);
    }
    pPreparedStatement->executeUpdate();

    delete pPreparedStatement;
}

void COrm::insertPlayer(SPlayer &Player)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement;
    unsigned short i = 1;
    if(Player.m_nUserId)
    {
        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Players` \
(`fk_Users_id`,`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`,`admin`) VALUES \
(?,?,?,?,?,?,?,?);");
        pPreparedStatement->setInt(i++, Player.m_nUserId);
    }
    else
    {
        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Players` \
(`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`,`admin`) VALUES \
(?,?,?,?,?,?,?);");
    }
    pPreparedStatement->setString(i++, Player.m_sName);
    pPreparedStatement->setString(i++, Player.m_sSurname);
    pPreparedStatement->setString(i++, Player.m_sPatronymic);
    pPreparedStatement->setString(i++, Player.m_sNick);
    pPreparedStatement->setString(i++, Player.m_sBirthDate);
    pPreparedStatement->setString(i++, Player.m_sQuenta);
    pPreparedStatement->setInt(i++, (int)(Player.m_bAdmin));
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertCredential(SCredential &Credential)
{
    qDebug() << __FUNCTION__;
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
    qDebug() << __FUNCTION__;
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
    qDebug() << __FUNCTION__;
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
    pPreparedStatement->setString(i++, SGroup::typeToString(Group.m_eType));
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertRole(SRole &Role)
{
    qDebug() << __FUNCTION__;
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

void COrm::insertNews(SNews &News)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `News` \
(`fk_Roles_id`,`created`,`subject`,`text`,`anonymously`,`shared`) VALUES \
(?,?,?,?,?,?);");
    pPreparedStatement->setInt(1, News.m_nRoleId);
    pPreparedStatement->setString(2, News.m_sCreatedDatetime);
    pPreparedStatement->setString(3, News.m_sSubject);
    pPreparedStatement->setString(4, News.m_sText);
    pPreparedStatement->setInt(5, (int)News.m_bAnonymously);
    pPreparedStatement->setInt(6, (int)News.m_bShared);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::insertItem(SItem Item)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Items` \
(`json_data`,`hash`) VALUES \
(?,?);");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, Item.m_sJsonData);
    pPreparedStatement->setString(i++, createUniqueHash());
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::updateUser(SUser &User)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `Users` \
SET `name`=?,`surname`=?,`patronymic`=?,`birth_date`=?,`profession`=?,`description`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, User.m_sName);
    pPreparedStatement->setString(i++, User.m_sSurname);
    pPreparedStatement->setString(i++, User.m_sPatronymic);
    pPreparedStatement->setString(i++, User.m_sBirthDate);
    pPreparedStatement->setString(i++, User.m_sProfession);
    pPreparedStatement->setString(i++, User.m_sDescription);
    pPreparedStatement->setInt(i++, User.m_nId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::updateUserStat(SUserStat &UserStat)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `hp_max`=?,`hp`=?,`pp`=?,`air`=?,`fk_Items_id_air`=?, `stun`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, UserStat.m_nHpMax);
    pPreparedStatement->setInt(i++, UserStat.m_nHp);
    pPreparedStatement->setInt(i++, UserStat.m_nPp);
    pPreparedStatement->setInt(i++, UserStat.m_nAir);
    if(UserStat.m_nAirId)
    {
        pPreparedStatement->setInt(i++, UserStat.m_nAirId);
    }
    else
    {
        pPreparedStatement->setNull(i++, 0);
    }
    pPreparedStatement->setInt(i++, UserStat.m_nStun);
    pPreparedStatement->setInt(i++, UserStat.m_nId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::updatePlayer(SPlayer &Player)
{

//    sql::PreparedStatement* pPreparedStatement;
//    unsigned short i = 1;
//    if(Player.m_nUserId)
//    {
//        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Players` \
//(`fk_Users_id`,`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`,`admin`) VALUES \
//(?,?,?,?,?,?,?,?);");
//        pPreparedStatement->setInt(i++, Player.m_nUserId);
//    }
//    else
//    {
//        pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Players` \
//(`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`,`admin`) VALUES \
//(?,?,?,?,?,?,?);");
//    }
//    pPreparedStatement->setString(i++, Player.m_sName);
//    pPreparedStatement->setString(i++, Player.m_sSurname);
//    pPreparedStatement->setString(i++, Player.m_sPatronymic);
//    pPreparedStatement->setString(i++, Player.m_sNick);
//    pPreparedStatement->setString(i++, Player.m_sBirthDate);
//    pPreparedStatement->setString(i++, Player.m_sQuenta);
//    pPreparedStatement->setInt(i++, (int)(Player.m_bAdmin));
//    pPreparedStatement->executeUpdate();
//    delete pPreparedStatement;

    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `Players` \
SET `fk_Users_id`=?,`name`=?,`surname`=?,`patronymic`=?,`nick`=?,`birth_date`=?,`quenta`=?,`admin`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Player.m_nUserId);
    pPreparedStatement->setString(i++, Player.m_sName);
    pPreparedStatement->setString(i++, Player.m_sSurname);
    pPreparedStatement->setString(i++, Player.m_sPatronymic);
    pPreparedStatement->setString(i++, Player.m_sNick);
    pPreparedStatement->setString(i++, Player.m_sBirthDate);
    pPreparedStatement->setString(i++, Player.m_sQuenta);
    pPreparedStatement->setInt(i++, (int)Player.m_bAdmin);
    pPreparedStatement->setInt(i++, Player.m_nId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;

}

void COrm::updateCredential(SCredential &Credential)
{
//    INSERT INTO table (id, name, age) VALUES(1, "A", 19) ON DUPLICATE KEY UPDATE    name="A", age=19

    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("INSERT INTO `Credentials` \
(`id`,`login`,`passwordHash`) VALUES \
(?,?,?) \
ON DUPLICATE KEY UPDATE \
login=?, passwordHash=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, Credential.m_nId);
    pPreparedStatement->setString(i++, Credential.m_sLogin);
    pPreparedStatement->setString(i++, Credential.m_sPasswordHash);
    pPreparedStatement->setString(i++, Credential.m_sLogin);
    pPreparedStatement->setString(i++, Credential.m_sPasswordHash);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::deleteHash(int &nHashId)
{

}

void COrm::deleteUser(int &nUserId)
{

}

void COrm::deletePlayer(int &nPlayerId)
{

}

void COrm::deleteCredential(int &nCredentialId)
{

}

void COrm::deleteGroup(int &nGroupId)
{

}

void COrm::deleteRole(int &nRoleId)
{

}

void COrm::deleteNews(int &nNewsId)
{

}

//SHash COrm::findHashByHashString(std::string sHash)
//{
//    qDebug() << __FUNCTION__;
//    SHash Result;
//    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
//select Hashs.id, \
//Hashs.hash \
//from Hashs \
//where Hashs.hash = ?;");
//    unsigned short i = 1;
//    pPreparedStatement->setString(i++, sHash);
//    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
//    while (pResult->next()) {
//        Result = SHash(pResult->getInt("id"),
//            pResult->getString("hash").c_str());
//    }
//    delete pResult;
//    delete pPreparedStatement;
//    return Result;
//}

SUser COrm::findUserByHashString(std::string sHash)
{
    qDebug() << __FUNCTION__;
    SUser Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Users.id, \
Users.name, \
Users.surname, \
Users.patronymic, \
Users.male, \
Users.birth_date, \
Users.specialty, \
Users.profession, \
Users.description \
from Users \
where Users.hash = ?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, sHash.c_str());
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SUser(pResult->getInt("id"),
            pResult->getString("name").c_str(),
            pResult->getString("surname").c_str(),
            pResult->getString("patronymic").c_str(),
            (bool)pResult->getInt("male"),
            pResult->getString("birth_date").c_str(),
            pResult->getString("specialty").c_str(),
            pResult->getString("profession").c_str(),
            pResult->getString("description").c_str());
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
//    SHash Hash = findHashByHashString(sHash);
    //    return findUserByHash(Hash);
}

SItem COrm::findItemByHashString(std::string sHash)
{
//    select * from Items where Items.hash = "b02d";
    qDebug() << __FUNCTION__;
    SItem Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select * \
from Items \
where Items.hash = ?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, sHash.c_str());
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SItem(pResult->getInt("id"),
            pResult->getString("json_data").c_str(),
            pResult->getString("hash").c_str());
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

//SUser COrm::findUserByHash(SHash Hash)
//{
//    qDebug() << __FUNCTION__;
//    SUser Result;
//    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
//select Users.id, \
//Users.name, \
//Users.surname, \
//Users.patronymic, \
//Users.birth_date, \
//Users.profession, \
//Users.description \
//from Users \
//where Users.fk_Hashs_id = ?;");
//    unsigned short i = 1;
//    pPreparedStatement->setInt(i++, Hash.m_nId);
//    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
//    while (pResult->next()) {
//        Result = SUser(pResult->getInt("id"),
//            pResult->getString("name").c_str(),
//            pResult->getString("surname").c_str(),
//            pResult->getString("patronymic").c_str(),
//            pResult->getString("birth_date").c_str(),
//            pResult->getString("profession").c_str(),
//            pResult->getString("description").c_str());
//    }
//    delete pResult;
//    delete pPreparedStatement;
//    return Result;
//}

void COrm::setHashStringToUser(std::string sHash, int nUserId)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `Users` \
SET `hash`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, sHash.c_str());
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

void COrm::setActionHashStringToUser(std::string sHash, int nUserId)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `Users` \
SET `action_hash`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setString(i++, sHash.c_str());
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

std::string COrm::getActionHashStringFromUser(int nUserId)
{
    qDebug() << __FUNCTION__;
    std::string sResult;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Users.action_hash \
from Users \
where Users.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nUserId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        sResult = pResult->getString("action_hash");
    }
    delete pResult;
    delete pPreparedStatement;
    return sResult;
}

//void COrm::deleteMessage(int &nMessageId)
//{

//}

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
                               (bool)pResult->getInt("male"),
                               pResult->getString("birth_date").c_str(),
                               pResult->getString("specialty").c_str(),
                               pResult->getString("profession").c_str(),
                               pResult->getString("description").c_str()));
    }
    delete pResult;
    return Result;
}

std::vector<SPlayer> COrm::selectPlayersAll()
{
    std::vector<SPlayer> Result;
    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("SELECT * FROM Players;");
    while (pResult->next()) {
        Result.push_back(SPlayer(pResult->getInt("id"),
            pResult->getInt("fk_Users_id"),
            pResult->getString("name").c_str(),
            pResult->getString("surname").c_str(),
            pResult->getString("patronymic").c_str(),
            pResult->getString("nick").c_str(),
            pResult->getString("birth_date").c_str(),
            pResult->getString("quenta").c_str(),
            pResult->getInt("admin")));
    }
    delete pResult;
    return Result;
}
CUser COrm::getUserByIdVisibleByAdmin(int nId)
{
    return getUserById(nId);
}

CUser COrm::getUserByIdVisibleByUser(int nId, int nWatcherUserId)
{
    CUser User = CUser(findUserById(nId));
    std::vector<SGroup> aGroupsVisibleByWatcher = selectAllGroupsVisibleByUser(nWatcherUserId);
    std::vector<SRole> UserRoles = findRolesByUserId(nId);
    for(size_t i = 0; i < UserRoles.size(); ++i)
    {
        int nCurRoleGroupId = UserRoles.at(i).m_nGroupId;
        for(size_t j = 0; j < aGroupsVisibleByWatcher.size(); ++j)
        {
            if(aGroupsVisibleByWatcher.at(j).m_nId == nCurRoleGroupId)
            {
                User.addGroup(findGroupById(nCurRoleGroupId));
                break;
            }
        }
    }
    return User;
}

CGroup COrm::getGroupInfoByIdVisibleByUser(int nId, int nWatcherUserId)
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> aGroupsVisibleByWatcher = selectAllGroupsVisibleByUser(nWatcherUserId);
    for(size_t j = 0; j < aGroupsVisibleByWatcher.size(); ++j)
    {
//        qDebug() << (aGroupsVisibleByWatcher.at(j).m_nId << nId;
        if(aGroupsVisibleByWatcher.at(j).m_nId == nId)
        {
            return getGroupInfoById(nId);
        }
    }
    return CGroup(SGroup());
}

CGroup COrm::getGroupInfoByIdVisibleByAdmin(int nId)
{
    return getGroupInfoById(nId);
}

CGroup COrm::getGroupInfoById(int nId)
{
    CGroup Group = CGroup(findGroupById(nId));
    std::vector<SRole> UserRoles = findRolesByGroupId(nId);
    for(size_t i = 0; i < UserRoles.size(); ++i)
    {
        Group.addUser(findUserById(UserRoles.at(i).m_nUserId));
    }
    return Group;
}

std::vector<CNews> COrm::selectNewsAll()
{
    std::vector<CNews> Result;
    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("select \
Roles.fk_Groups_id, \
Roles.fk_Users_id, \
News.id, \
News.created, \
News.subject, \
News.text, \
News.anonymously, \
News.fk_Roles_id, \
News.shared \
from News \
join Roles \
on News.fk_Roles_id = Roles.id \
where News.shared = 1 \
order by News.created desc \
;");
    while (pResult->next())
    {
        int nGroupId = pResult->getInt("fk_Groups_id");
        int nAuthorId = pResult->getInt("fk_Users_id");

        SNews PreNews = SNews(pResult->getInt("id"),
                              pResult->getInt("fk_Roles_id"),
                              pResult->getString("created").c_str(),
                              pResult->getString("subject").c_str(),
                              pResult->getString("text").c_str(),
                              pResult->getInt("anonymously"),
                              pResult->getInt("shared"));
        CNews News = CNews(PreNews);
        if(!PreNews.m_bAnonymously)
        {
            News.addAuthor(findUserById(nAuthorId));
        }
        News.addGroup(findGroupById(nGroupId));
        Result.push_back(News);

    }
    delete pResult;
    return Result;
}

std::vector<SGroup> COrm::selectAllGroupsVisibleByUser(int nId)
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> Result;

//    SPlayer Player = findPlayerById(nId);

    sql::PreparedStatement* pPreparedStatement;
//    if(Player.m_bAdmin)
//    {
//        pPreparedStatement = m_pCSqlConnector->prepare("\
//select Groups.id, \
//Groups.fk_Groups_id_parent, \
//Groups.name, \
//Groups.description, \
//Groups.type \
//from Groups");
//    }
//    else
//    {
        pPreparedStatement = m_pCSqlConnector->prepare("\
select ChildGroups.id, \
ChildGroups.fk_Groups_id_parent, \
ChildGroups.name, \
ChildGroups.description, \
ChildGroups.type \
from Groups as ChildGroups \
join Groups \
on Groups.id = ChildGroups.fk_Groups_id_parent \
join Roles \
on Groups.id = Roles.fk_Groups_id \
join Users \
on Users.id = Roles.fk_Users_id \
where Users.id = ? \
and ChildGroups.type != 'hidden'\
\
UNION \
\
select Groups.id, \
Groups.fk_Groups_id_parent, \
Groups.name, \
Groups.description, \
Groups.type \
from Groups \
join Roles \
on Groups.id = Roles.fk_Groups_id \
join Users \
on Users.id = Roles.fk_Users_id \
where Users.id = ? \
\
UNION \
\
select Groups.id, \
Groups.fk_Groups_id_parent, \
Groups.name, \
Groups.description, \
Groups.type \
from Groups \
where Groups.type = 'lab'\
or Groups.type = 'public';");
        unsigned short i = 1;
        pPreparedStatement->setInt(i++, nId);
        pPreparedStatement->setInt(i++, nId);
//    }
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(SGroup(pResult->getInt("id"),
            pResult->getInt("fk_Groups_id_parent"),
            pResult->getString("name").c_str(),
            pResult->getString("description").c_str(),
            pResult->getString("type").c_str()));
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

void COrm::stunUserId(int nStun, int nUserId)
{
    qDebug() << __FUNCTION__;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `stun`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nStun);
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

bool COrm::switchAirType(int nInitAirSeconds, int nUserId)
{
    qDebug() << __FUNCTION__;

    SUserStat Stat = findUserStatsById(nUserId);
    int nNewAir = -1;
    if(Stat.m_nAir == -1)
    {
        nNewAir = nInitAirSeconds;
    }

    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `air`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nNewAir);
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
    return nNewAir > 0;
}

EUserStates COrm::modifyAirUserId(int nDelta, int nUserId)
{
    qDebug() << __FUNCTION__;

    SUserStat Stat = findUserStatsById(nUserId);
    if(Stat.m_nHp == 0)
    {
        return AlreadyDead;
    }
    int nNewHp = Stat.m_nHp + nDelta;
    if(nNewHp > Stat.m_nHpMax)
    {
        nNewHp = Stat.m_nHpMax;
    }
    else if(nNewHp < 0)
    {
        nNewHp = 0;
    }

    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `hp`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nNewHp);
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;

    if(nDelta > 0)
    {
        if(Stat.m_nHp == Stat.m_nHpMax)
        {
            return AlreadyFull;
        }
        else if(nNewHp == Stat.m_nHpMax)
        {
            return HealedToCap;
        }
        else
        {
            return Healed;
        }
    }
    else
    {
        if(nNewHp == 0)
        {
            return Died;
        }
        else
        {
            return Damaged;
        }
    }
}

EUserStates COrm::modifyHealthUserId(int nDelta, int nUserId)
{
    qDebug() << __FUNCTION__;

    SUserStat Stat = findUserStatsById(nUserId);
    if(Stat.m_nHp == 0)
    {
        return AlreadyDead;
    }
    int nNewHp = Stat.m_nHp + nDelta;
    if(nNewHp > Stat.m_nHpMax)
    {
        nNewHp = Stat.m_nHpMax;
    }
    else if(nNewHp < 0)
    {
        nNewHp = 0;
    }

    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `hp`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nNewHp);
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;

    if(nDelta > 0)
    {
        if(Stat.m_nHp == Stat.m_nHpMax)
        {
            return AlreadyFull;
        }
        else if(nNewHp == Stat.m_nHpMax)
        {
            return HealedToCap;
        }
        else
        {
            return Healed;
        }
    }
    else
    {
        if(nNewHp == 0)
        {
            return Died;
        }
        else
        {
            return Damaged;
        }
    }
}

void COrm::modifyPsyUserId(int nDelta, int nUserId)
{
    qDebug() << __FUNCTION__;

    SUserStat Stat = findUserStatsById(nUserId);
    int nNewPp = Stat.m_nPp + nDelta;
    if(nNewPp > 100)
    {
        nNewPp = 100;
    }
    else if(nNewPp < 0)
    {
        nNewPp = 0;
    }

    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("UPDATE `UserStats` \
SET `pp`=? \
WHERE id=?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nNewPp);
    pPreparedStatement->setInt(i++, nUserId);
    pPreparedStatement->executeUpdate();
    delete pPreparedStatement;
}

std::vector<SUserStat> COrm::selectUserStatsAll()
{
    qDebug() << __FUNCTION__;

    std::vector<SUserStat> Result;
    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("SELECT * FROM UserStats;");
    while (pResult->next()) {
        Result.push_back(SUserStat(pResult->getInt("id"),
                                   pResult->getInt("hp_max"),
                                   pResult->getInt("hp"),
                                   pResult->getInt("pp"),
                                   pResult->getInt("air"),
                                   pResult->getInt("fk_Items_id_air"),
                                   pResult->getInt("stun")));
    }
    delete pResult;
    return Result;
}

std::string COrm::createUniqueHash()
{
    qDebug() << __FUNCTION__;
    std::string sNewHash;
    bool bFound = false;
    int nHashsGenerated = 0;
    do
    {
        QString sTime = QString::number(QDateTime::currentMSecsSinceEpoch() + nHashsGenerated++);
        QString sHash = QCryptographicHash::hash(sTime.toUtf8(), QCryptographicHash::Md5).toHex();
        sNewHash = sHash.left(HASH_LEN).toStdString();

        SUser User = findUserByHashString(sNewHash);
        if(User.m_nId > 0)
        {
            qDebug() << "user with such hash found";
            bFound = true;
            continue;
        }
        SItem Item = findItemByHashString(sNewHash);
        if(Item.m_nId > 0)
        {
            qDebug() << "item with such hash found";
            bFound = true;
            continue;
        }
    }
    while(bFound == true);
    qDebug() << "new unique hash" << sNewHash.c_str();
    return sNewHash;
}

std::vector<SGroup> COrm::selectAllGroupsVisibleByAdmin()
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> Result;

    sql::PreparedStatement* pPreparedStatement;
    pPreparedStatement = m_pCSqlConnector->prepare("\
select Groups.id, \
Groups.fk_Groups_id_parent, \
Groups.name, \
Groups.description, \
Groups.type \
from Groups");
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(SGroup(pResult->getInt("id"),
            pResult->getInt("fk_Groups_id_parent"),
            pResult->getString("name").c_str(),
            pResult->getString("description").c_str(),
            pResult->getString("type").c_str()));
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

std::vector<CNews> COrm::selectNewsAllVisibleByUser(int nWatcherId)
{
    /// TODO use selectNewsAll and then filter them
    std::vector<SGroup> aGroupsVisibleByWatcher = selectAllGroupsVisibleByUser(nWatcherId);
    std::vector<CNews> Result;
    sql::ResultSet* pResult = m_pCSqlConnector->executeResult("select \
Roles.fk_Groups_id, \
Roles.fk_Users_id, \
News.id, \
News.created, \
News.subject, \
News.text, \
News.anonymously, \
News.fk_Roles_id, \
News.shared \
from News \
join Roles \
on News.fk_Roles_id = Roles.id \
where News.shared = 1 \
order by News.created desc \
;");
    while (pResult->next())
    {
        int nGroupId = pResult->getInt("fk_Groups_id");
        int nAuthorId = pResult->getInt("fk_Users_id");
        for(size_t j = 0; j < aGroupsVisibleByWatcher.size(); ++j)
        {
            if(aGroupsVisibleByWatcher.at(j).m_nId == nGroupId)
            {
                SNews PreNews = SNews(pResult->getInt("id"),
                                      pResult->getInt("fk_Roles_id"),
                                      pResult->getString("created").c_str(),
                                      pResult->getString("subject").c_str(),
                                      pResult->getString("text").c_str(),
                                      pResult->getInt("anonymously"),
                                      pResult->getInt("shared"));
                CNews News = CNews(PreNews);
                if(!PreNews.m_bAnonymously)
                {
                    News.addAuthor(findUserById(nAuthorId));
                }
                News.addGroup(findGroupById(nGroupId));
                Result.push_back(News);

                break;
            }
        }
    }
    delete pResult;
    return Result;
}

std::vector<CNews> COrm::selectNewsAllVisibleByAdmin()
{
    return selectNewsAll();
}

/*std::vector<CGroup> COrm::selectAllGroupsInfoVisibleByUser(int nId)
{
    qDebug() << __FUNCTION__;
    std::vector<CGroup> Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select ChildGroups.id \
from Groups as ChildGroups \
join Groups \
on Groups.id = ChildGroups.fk_Groups_id_parent \
join Roles \
on Groups.id = Roles.fk_Groups_id \
join Users \
on Users.id = Roles.fk_Users_id \
where Users.id = ? \
and ChildGroups.type != 'hidden'\
\
UNION \
\
select Groups.id \
from Groups \
join Roles \
on Groups.id = Roles.fk_Groups_id \
join Users \
on Users.id = Roles.fk_Users_id \
where Users.id = ? \
\
UNION \
\
select Groups.id \
from Groups \
where Groups.type = 'lab'\
or Groups.type = 'public';");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(getGroupInfoById(pResult->getInt("id")));
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}*/

std::vector<SGroup> COrm::selectGroupsAll()
{
    qDebug() << __FUNCTION__;
    std::vector<SGroup> Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select Groups.id, \
Groups.fk_Groups_id_parent, \
Groups.name, \
Groups.description, \
Groups.type \
from Groups;");
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(SGroup(pResult->getInt("id"),
            pResult->getInt("fk_Groups_id_parent"),
            pResult->getString("name").c_str(),
            pResult->getString("description").c_str(),
            pResult->getString("type").c_str()));
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
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
Users.male, \
Users.birth_date, \
Users.specialty, \
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
                       (bool)pResult->getInt("male"),
                       pResult->getString("birth_date").c_str(),
                       pResult->getString("specialty").c_str(),
                       pResult->getString("profession").c_str(),
                       pResult->getString("description").c_str());
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

SUserStat COrm::findUserStatsById(int nId)
{
    qDebug() << __FUNCTION__;
    SUserStat Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select * \
from UserStats \
where UserStats.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SUserStat(pResult->getInt("id"),
                       pResult->getInt("hp_max"),
                       pResult->getInt("hp"),
                       pResult->getInt("pp"),
                       pResult->getInt("air"),
                       pResult->getInt("fk_Items_id_air"),
                       pResult->getInt("stun"));
    }
    delete pResult;
    delete pPreparedStatement;
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
Players.quenta, \
Players.admin \
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
        Result = SPlayer(
                    pResult->getInt("id"),
                    pResult->getInt("fk_Users_id"),
                    pResult->getString("name").c_str(),
                    pResult->getString("surname").c_str(),
                    pResult->getString("patronymic").c_str(),
                    pResult->getString("nick").c_str(),
                    pResult->getString("birth_date").c_str(),
                    pResult->getString("quenta").c_str(),
                    (bool)pResult->getInt("admin")
        );
    }
    delete pResult;
    delete pPreparedStatement;
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
Players.quenta, \
Players.admin \
from Players \
where Players.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SPlayer(
                    pResult->getInt("id"),
                    pResult->getInt("fk_Users_id"),
                    pResult->getString("name").c_str(),
                    pResult->getString("surname").c_str(),
                    pResult->getString("patronymic").c_str(),
                    pResult->getString("nick").c_str(),
                    pResult->getString("birth_date").c_str(),
                    pResult->getString("quenta").c_str(),
                    (bool)pResult->getInt("admin")
        );
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

SPlayer COrm::findPlayerByUserId(int nUserId)
{
    qDebug() << __FUNCTION__;
    SPlayer Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select * \
from Players \
where Players.fk_Users_id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nUserId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SPlayer(
                    pResult->getInt("id"),
                    pResult->getInt("fk_Users_id"),
                    pResult->getString("name").c_str(),
                    pResult->getString("surname").c_str(),
                    pResult->getString("patronymic").c_str(),
                    pResult->getString("nick").c_str(),
                    pResult->getString("birth_date").c_str(),
                    pResult->getString("quenta").c_str(),
                    (bool)pResult->getInt("admin")
        );
    }
    delete pResult;
    delete pPreparedStatement;
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
    delete pPreparedStatement;
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
    delete pPreparedStatement;
    return Result;
}

std::vector<SRole> COrm::findRolesByGroupId(int nGroupId)
{
    qDebug() << __FUNCTION__;
    std::vector<SRole> Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select id, \
fk_Users_id, \
fk_Groups_id, \
owner \
from Roles \
where fk_Groups_id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nGroupId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result.push_back(SRole(pResult->getInt("id"),
            pResult->getInt("fk_Users_id"),
            pResult->getInt("fk_Groups_id"),
            (bool)(pResult->getInt("owner"))));
    }
    delete pResult;
    delete pPreparedStatement;
    return Result;
}

SItem COrm::findItemById(int nId)
{
    qDebug() << __FUNCTION__;
    SItem Result;
    sql::PreparedStatement* pPreparedStatement = m_pCSqlConnector->prepare("\
select * \
from Items \
where Items.id = ?;");
    unsigned short i = 1;
    pPreparedStatement->setInt(i++, nId);
    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
    while (pResult->next()) {
        Result = SItem(pResult->getInt("id"),
            pResult->getString("json_data").c_str(),
            pResult->getString("hash").c_str());
    }
    delete pResult;
    delete pPreparedStatement;
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
    m_pCSqlConnector->execute(NEWS_DROP_SCRIPT);
    m_pCSqlConnector->execute(USER_STAT_DROP_SCRIPT);
    m_pCSqlConnector->execute(ITEM_DROP_SCRIPT);
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
    m_pCSqlConnector->execute(NEWS_CREATE_SCRIPT);
    m_pCSqlConnector->execute(USER_STAT_CREATE_SCRIPT);
    m_pCSqlConnector->execute(ITEM_CREATE_SCRIPT);

    m_pCSqlConnector->execute(PLAYER_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_CONNECT_SCRIPT_1);
    m_pCSqlConnector->execute(MESSAGE_CONNECT_SCRIPT_2);
    m_pCSqlConnector->execute(GROUP_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(ROLE_CONNECT_SCRIPT_1);
    m_pCSqlConnector->execute(ROLE_CONNECT_SCRIPT_2);
    m_pCSqlConnector->execute(NEWS_CONNECT_SCRIPT);
    m_pCSqlConnector->execute(USER_STAT_CONNECT_SCRIPT_1);
    m_pCSqlConnector->execute(USER_STAT_CONNECT_SCRIPT_2);

    m_pCSqlConnector->execute(USER_UTF8_SCRIPT);
    m_pCSqlConnector->execute(PLAYER_UTF8_SCRIPT);
    m_pCSqlConnector->execute(CREDENTIAL_UTF8_SCRIPT);
    m_pCSqlConnector->execute(MESSAGE_UTF8_SCRIPT);
    m_pCSqlConnector->execute(GROUP_UTF8_SCRIPT);
    m_pCSqlConnector->execute(ROLE_UTF8_SCRIPT);
    m_pCSqlConnector->execute(NEWS_UTF8_SCRIPT);
    m_pCSqlConnector->execute(USER_STAT_UTF8_SCRIPT);
    m_pCSqlConnector->execute(ITEM_UTF8_SCRIPT);
    /// keys
    enableForingKeys();
}

CUser COrm::getUserById(int nId)
{
    CUser User = CUser(findUserById(nId));
    std::vector<SRole> UserRoles = findRolesByUserId(nId);
    for(size_t i = 0; i < UserRoles.size(); ++i)
    {
        int nCurRoleGroupId = UserRoles.at(i).m_nGroupId;
        User.addGroup(findGroupById(nCurRoleGroupId));
    }
    return User;
}
