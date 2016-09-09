#include "cserverlogic.h"

CServerLogic::CServerLogic(COrm *pOrm):
    m_pOrm(pOrm)
{
    SHealShot HealShot;
    QString sHealHash = m_pOrm->insertItem(HealShot.toItem());
    SAirlock Airlock;
    QString sAirlockHash = m_pOrm->insertItem(Airlock.toItem());
    SAirCell AirCell;
    QString sAirCellHash = m_pOrm->insertItem(AirCell.toItem());

    m_pOrm->insertLore(SLore("Добро поаловать в 'Архив'!", "Здесь Вы можете ознакомиться с основными функциями различных разделов портала базы, "
                                                   "после чего получить дальнейшие инструкции по проведению тестирования."));
    m_pOrm->insertLore(SLore("Описание разделов", "Портал базы состоит из разделов. "
                     "Лента содержит в себе новости из всех видимых Вам лабораторий и групп. "
                     "'Статус' показывает наиболее важные аспекты Вашего текущего состояния. "
                     "Разел 'Воздействия' используется для взаимодействия с приборами и полезными объектами, например, для ввода лечебной сыворотки. "
                     "В разделе 'Проекты' отображены все видимые Вам проекты. "
                     "Сходным образом в разделе 'Люди' показан полный список персонала базы. "
                     "Открытый в данный момент раздел 'Архив' содержит полезную информацию общего характера. "
                     "'Профиль' позволяет увидеть публичную информацию о Вас, а так же ознакомиться с более подробной личной информацией"
                     "Ну и, наконец, 'Выход' позволяет Вам выйти с портала базы. "
                     "Пожалуйста, пробегитесь по разделам, убедитесь, что они открываются, что содержимое соответствует названию, "
                     "если всё в порядке, переходите к тестированию, удачи!"));
    m_pOrm->insertLore(SLore("Задание для тестирования", "Одна из основных задач портала - слежение за Вашим состоянием, поэтому следующим заданием будет "
                                    "перейти в раздел 'Статус' и отметить получение повреждения, нажав на кнопку '-'рядом с показателем Вашего здоровья "
                     "при этом Ваше состояние должно измениться, проконтролируйте это, пожалуйста. "
                     "Отметив повреждения, Вы получете возможность протестировать работу лечебной сыворотки. "
                     "Для этого в нормальной ситуации Вам нужен был бы код с капсулы с сывороткой, но в рамках тестирования просто примените этот код:"
                     + sHealHash +". "
                     "Для чего перейдите в раздел 'Воздействия', введите этот код в поле 'Код' и нажмите 'Считать код'. "
                     "После этих действий должна появиться панель взаимодействия с сывороткой, в которой будет одной действие - 'Принять', "
                     "нажмите на кнопку и убедитесь в изменении Вашего статуса. "
                     "Следующим заданием будет выход со станции через центральный шлюз, ситуация с кодом шлюза аналогична - "
                     "в норме вы должны считывать код шлюза непосредственно с него, в режиме тестирования Вам достаточно ввести этот код:"+sAirlockHash+
                     " и откроется панель шлюза, пройдите через него, вы начнёте задыхаться, что будет отображено в разделе 'статус', не бойтесь, "
                     "атмосфера планеты не настолько смертельна, у Вас в запасе есть пара минут, надеюсь, Вам этого хватит, чтобы ввести код кислородной "
                     "ячейки:"+sAirCellHash+" После активации кислородной ячейки проверьте свой статус и вернитесь на базу."
                     "Минимальный цикл тестов на этом заканчивается, пожалуйста, напишите отчёт, обязательно сообщите, "
                     "удалось ли Вам выполнить вышеописанные шаги, если где-то возникли трудности, не забудьте о них рассказать, спасибо!"));

//    m_pOrm->insertLore(SLore("Дополнительное задание для тестирования", "Для выполнения этого задания Вам потребуется напраник, так же имеющий доступ к системе базы. "
//                     "Ваш напарник должен войти в раздел 'Воздействия '"));
}

//SPlayer CServerLogic::login(QString sLogin, QString sPassword)
//{
//    qDebug() << __FUNCTION__;
//    SPlayer Player = m_pOrm->findPlayerByLoginAndPassHash(sLogin, sPassword);
//    return Player;
//}
QPair<int, bool> CServerLogic::login(QString sLogin, QString sPassword)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerByLoginAndPassHash(sLogin, sPassword);
    return QPair<int, bool>(Player.m_nId, Player.m_bAdmin);
}

//SPlayer CServerLogic::getPlayerById(int nId)
//{
//    qDebug() << __FUNCTION__;
//    SPlayer Player = m_pOrm->findPlayerById(nId);

//    return Player;
//}

bool CServerLogic::CheckAdminByPlayerId(int nId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nId);

    return Player.m_bAdmin;
}

QPair<int, bool> CServerLogic::getUserIdAndIsAdminByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nPlayerId);

    return QPair<int, bool>(Player.m_nUserId, Player.m_bAdmin);
}

int CServerLogic::getPlayerIdByUserId(int nUserId)
{
    SPlayer Player = m_pOrm->findPlayerByUserId(nUserId);
    return Player.m_nId;
}

QByteArray CServerLogic::getPlayerData(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = m_pOrm->findPlayerById(nPlayerId);

    return Player.getJson();
}

QByteArray CServerLogic::getPlayersAll()
{
    qDebug() << __FUNCTION__;
    std::vector<SPlayer> aPlayers = m_pOrm->selectPlayersAll();

    QJsonArray jArray;
    for(size_t i = 0; i < aPlayers.size(); ++i)
    {
        QJsonValue jValue(aPlayers[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

QByteArray CServerLogic::getUserByIdVisibleByPlayerId(int nUserId, int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    CUser User;
    if(bIsAbdmin)
    {
        User = m_pOrm->getUserByIdVisibleByAdmin(nUserId);
    }
    else
    {
        User = m_pOrm->getUserByIdVisibleByUser(nUserId, nWatcherUserId);
    }
    return User.getJson();
}

QByteArray CServerLogic::getUsersAllData()
{
    qDebug() << __FUNCTION__;
    std::vector<SUser> Users = m_pOrm->selectUserAll();

    QJsonArray jArray;
    for(size_t i = 0; i < Users.size(); ++i)
    {
        QJsonValue jValue(Users[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

QByteArray CServerLogic::getUserStatusVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    SUserStat Stat = m_pOrm->findUserStatsById(nWatcherUserId);
    return Stat.getJson();
}

QByteArray CServerLogic::getProjectByIdVisibleByPlayerId(int nProjectId, int nPlayerId)
{
    qDebug() << __FUNCTION__ << nProjectId << nPlayerId;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    CGroup Group;
    if(bIsAbdmin)
    {
        Group = m_pOrm->getGroupInfoByIdVisibleByAdmin(nProjectId);
    }
    else
    {
        Group = m_pOrm->getGroupInfoByIdVisibleByUser(nProjectId, nWatcherUserId);
    }

    if(Group.notEmpty() == true)
    {
        Group.setNews(m_pOrm->selectNewsByGroup(nProjectId));
    }

    return Group.getJson();
}

QByteArray CServerLogic::getProjectsAllVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    std::vector<SGroup> aGroups;
    if(bIsAbdmin)
    {
        aGroups = m_pOrm->selectAllGroupsVisibleByAdmin();
    }
    else
    {
        aGroups = m_pOrm->selectAllGroupsVisibleByUser(nWatcherUserId);
    }
    qDebug() << aGroups.size();


    QJsonArray jArray;
    for(size_t i = 0; i < aGroups.size(); ++i)
    {
        QJsonValue jValue(aGroups[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}
/// deprecated
//QByteArray CServerLogic::getProjectsAllData()
//{
//    qDebug() << __FUNCTION__;
//    std::vector<SGroup> aGroups = m_pOrm->selectGroupsAll();


//    QJsonArray jArray;
//    for(size_t i = 0; i < aGroups.size(); ++i)
//    {
//        QJsonValue jValue(aGroups[i].getJsonObject());
//        jArray.append(jValue);
//    }

//    QJsonDocument jDocument;
//    jDocument.setArray(jArray);
//    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    return aJson;
//}

QByteArray CServerLogic::getNewsAllVisibleByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    bool bIsAbdmin = UserIdAndIsAdmin.second;

    std::vector<CNews> aNews;
    if(bIsAbdmin)
    {
        aNews = m_pOrm->selectNewsAllVisibleByAdmin();
    }
    else
    {
        aNews = m_pOrm->selectNewsAllVisibleByUser(nWatcherUserId);
    }

    QJsonArray jArray;
    for(size_t i = 0; i < aNews.size(); ++i)
    {
        QJsonValue jValue(aNews[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

bool CServerLogic::addPlayer(QByteArray jPlayer)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = SPlayer::getObjectFromJson(jPlayer);
    if(Player.m_sName.isEmpty())
    {
        return false;
    }
    m_pOrm->insertPlayer(Player);
    return true;
}

bool CServerLogic::updatePlayer(QByteArray jPlayer)
{
    qDebug() << __FUNCTION__;
    SPlayer Player = SPlayer::getObjectFromJson(jPlayer);
    if(Player.m_nId)
    {
        m_pOrm->updatePlayer(Player);
        return true;
    }
    return false;
}

bool CServerLogic::updatePlayerCredential(QByteArray jCredential)
{
    qDebug() << __FUNCTION__;
    SCredential Credential = SCredential::getObjectFromJson(jCredential);
    if(Credential.m_nId)
    {
        m_pOrm->updateCredential(Credential);
        return true;
    }
    return false;
}

bool CServerLogic::deletePlayer(int nPlayerId)
{
    //    m_pOrm->insertUser(User);
        return false;
}

bool CServerLogic::addUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;
    SUser User = SUser::getObjectFromJson(jUser);
    if(User.m_sName.isEmpty())
    {
        return false;
    }
    SUserStat UserStat(5, 5, 10, 900, 0);
    m_pOrm->insertUser(User, UserStat);
    return true;
}

bool CServerLogic::updateUser(QByteArray jUser)
{
    qDebug() << __FUNCTION__;

    SUser User = SUser::getObjectFromJson(jUser);
    if(User.m_nId)
    {
        m_pOrm->updateUser(User);
        return true;
    }
    return false;
}

bool CServerLogic::deleteUser(int nUserId)
{
//    m_pOrm->insertUser(User);
    return false;
}

QByteArray CServerLogic::genereateNewHashForUserByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    QString sNewHash = m_pOrm->createUniqueHash();

    m_pOrm->setHashStringToUser(sNewHash, nWatcherUserId);

    return QByteArray(("{\"value\": \"" + sNewHash.toLatin1() + "\"}"));
}

QByteArray CServerLogic::useItemByHashByPlayerId(QString sHash, int nPlayerId)
{
    /// TODO add some skills checks here

    QByteArray Result = getActionsByHash(sHash);
    if(Result.isEmpty())
    {
        return Result;
    }

    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    m_pOrm->setActionHashStringToUser(sHash, nWatcherUserId);

    return Result;
}

QByteArray CServerLogic::getActionsByHash(QString sHash)
{
    qDebug() << __FUNCTION__;

    SUser User = m_pOrm->findUserByHashString(sHash);
    if(User.m_nId > 0)
    {
        qDebug() << "user found";
        return QByteArray(("{\"object\": \"" + User.m_sSurname.toLatin1()
                           + " "  + User.m_sName.toLatin1()
                           + " "  + User.m_sPatronymic.toLatin1()
                          + "\", \"data\": \"Человек\", \"actions\": [\"Взять анализ крови\", \"Оглушить\"]}"));
    }

    SItem Item = m_pOrm->findItemByHashString(sHash);
    if(Item.m_nId > 0)
    {
        qDebug() << "item found";
        IItem* pItem = CItemManager::parseItem(Item);
        if(pItem == 0)
        {
            qDebug() << "got 0 pointer from parser";
            return QByteArray();
        }
        return QByteArray(("{\"object\": \"" + pItem->getName()
                           + "\", \"data\": \"" + pItem->getType()
                           + "\", \"actions\": " + stringListToString(pItem->getActions()) + "}").toUtf8());
    }
    qDebug() << "nothing found";
    return QByteArray();
}

QByteArray CServerLogic::actionByPlayerId(QString sAction, int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;

    QString sTargetHash = m_pOrm->getActionHashStringFromUser(nWatcherUserId);

    SUser TargetUser = m_pOrm->findUserByHashString(sTargetHash);
    if(TargetUser.m_nId > 0)
    {
        qDebug() << "user found";
        if(sAction == "Оглушить")
        {
            m_pOrm->stunUserId(DEFAULT_STUN_SEC, TargetUser.m_nId);
            int nTargetPlayerId = getPlayerIdByUserId(TargetUser.m_nId);
            if(nTargetPlayerId > 0)
            {
                emit statusChange("Оглушен", nTargetPlayerId);
            }
            return QByteArray("qr action accepted:");
        }
        else if(sAction == "Взять анализ крови")
        {
            int nTargetPlayerId = getPlayerIdByUserId(TargetUser.m_nId);
            if(nTargetPlayerId > 0)
            {
                emit statusChange("У Вас взяли анализ крови", nTargetPlayerId);
                emit statusChange("Вы взяли анализ крови", nPlayerId);
            }
            return QByteArray("qr action accepted:");
        }
    }

    SItem Item = m_pOrm->findItemByHashString(sTargetHash);
    if(Item.m_nId > 0)
    {
        qDebug() << "item found";
        IItem* pItem = CItemManager::parseItem(Item);
        if(pItem == 0)
        {
            qDebug() << "got 0 pointer from parser";
            return QByteArray("internal error:");
        }
        else if(pItem->eType == HealShot)
        {
            int nTargetPlayerId = getPlayerIdByUserId(nWatcherUserId);
            if(sAction == USE_HEALSHOT)
            {
                EUserStates eState = m_pOrm->modifyHealthUserId(1, nWatcherUserId);
                if(eState == AlreadyDead)
                {
                    emit statusChange("На Вас применено лекарство, однако, Вы уже мертвы и лекарство не помогает", nTargetPlayerId);
                }
                else if(eState == Healed)
                {
                    emit statusChange("На Вас применено лекарство, часть Вашего здоровья восстановлена", nTargetPlayerId);
                }
                else if(eState == HealedToCap)
                {
                    emit statusChange("На Вас применено лекарство, Вы более не ранены", nTargetPlayerId);
                }
                else if(eState == AlreadyFull)
                {
                    emit statusChange("На Вас применено лекарство, однако, Вы и так были здоровы", nTargetPlayerId);
                }
                emit qrClosed(nPlayerId);
                return QByteArray("qr action accepted:");
            }
        }
        else if(pItem->eType == Airlock)
        {
            int nTargetPlayerId = getPlayerIdByUserId(nWatcherUserId);
            if(sAction == USE_AIRLOCK)
            {
                bool bIsOutside = m_pOrm->switchAirType(DEFAULT_AIR_SEC, nWatcherUserId);
                if(bIsOutside){
                    emit statusChange("Вы вышли со станции", nTargetPlayerId);
                }
                else
                {
                    emit statusChange("Вы вошли на станцию", nTargetPlayerId);
                }
                emit qrClosed(nPlayerId);
                return QByteArray("qr action accepted:");
            }
        }
        else if(pItem->eType == AirCell)
        {
            int nTargetPlayerId = getPlayerIdByUserId(nWatcherUserId);
            if(sAction == USE_AIRCELL)
            {
                EUserStates eState = m_pOrm->modifyAirUserId(DEFAULT_AIRCELL_SIZE_SEC, nWatcherUserId);
                if(eState == AlreadyDead)
                {
                    emit statusChange("На Вас применена кислородная ячейка, однако, Вы уже мертвы", nTargetPlayerId);
                }
                else
                {
                    emit statusChange("Вы использовали кислородную ячейку", nTargetPlayerId);
                }
                emit qrClosed(nPlayerId);
                return QByteArray("qr action accepted:");
            }
        }
        return QByteArray(("{\"object\": \"" + pItem->getName()
                           + "\", \"data\": \"" + pItem->getType()
                           + "\", \"actions\": " + stringListToString(pItem->getActions()) + "}").toUtf8());
    }
    return QByteArray("target not found:");
}

void CServerLogic::healthLossByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    EUserStates eState = m_pOrm->modifyHealthUserId(-1, nWatcherUserId);
    if(eState == AlreadyDead)
    {
        emit statusChange("Вы уже мертвы, Вы не можете стать ещё мертвее", nPlayerId);
    }
    else if(eState == Died)
    {
        emit statusChange("Вы погибли!", nPlayerId);
    }
    else if(eState == Damaged)
    {
        emit statusChange("Вы ранены!", nPlayerId);
    }
}
void CServerLogic::psyLossByPlayerId(int nPlayerId)
{
    qDebug() << __FUNCTION__;
    QPair<int, bool> UserIdAndIsAdmin = getUserIdAndIsAdminByPlayerId(nPlayerId);
    int nWatcherUserId = UserIdAndIsAdmin.first;
    m_pOrm->modifyPsyUserId(-5, nWatcherUserId);
    emit statusChange("Ваша психика стала менее устойчива", nPlayerId);
}

QByteArray CServerLogic::getLore()
{
    qDebug() << __FUNCTION__;

    std::vector<SLore> aLores = m_pOrm->getAllLores();

    QJsonArray jArray;
    for(size_t i = 0; i < aLores.size(); ++i)
    {
        QJsonValue jValue(aLores[i].getJsonObject());
        jArray.append(jValue);
    }

    QJsonDocument jDocument;
    jDocument.setArray(jArray);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

//QByteArray CServerLogic::getJsonFromUser(SUser &User)
//{
//    QJsonObject jUser;
//    jUser.insert("Id", User.m_nId);
//    jUser.insert("Name", User.m_sName);
//    jUser.insert("Surname", User.m_sSurname);
//    jUser.insert("Patronymic", User.m_sPatronymic);
//    jUser.insert("BirthDate", User.m_sBirthDate);
//    jUser.insert("Profession", User.m_sProfession);
//    jUser.insert("Description", User.m_sDescription);

//    QJsonDocument jDocument;
//    jDocument.setObject(jUser);
//    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    return aJson;
//}

