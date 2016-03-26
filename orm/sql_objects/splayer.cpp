#include "splayer.h"

SPlayer::SPlayer(){}

SPlayer::SPlayer(std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

SPlayer::SPlayer(int nUserId, std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_nUserId(nUserId),
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

SPlayer::SPlayer(int nId, int nUserId, std::string sName, std::string sSurname, std::string sPatronymic, std::string sNick, std::string sBirthDate, std::string sQuenta, bool bAdmin):
    m_nId(nId),
    m_nUserId(nUserId),
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),
    m_sNick(sNick),
    m_sBirthDate(sBirthDate),
    m_sQuenta(sQuenta),
    m_bAdmin(bAdmin)
{}

/// <-- Constructors
/////////////////////////////////////////////////////////////////////////
///// Queries -->

//void SPlayer::insertPlayer(CSqlConnector* pCSqlConnector, SPlayer &Player)
//{
//    sql::PreparedStatement* pPreparedStatement;
//    unsigned short i = 1;
//    if(Player.m_nUserId)
//    {
//        pPreparedStatement = pCSqlConnector->prepare("INSERT INTO `Players` \
//(`fk_Users_id`,`name`,`surname`,`patronymic`,`nick`,`birth_date`,`quenta`,`admin`) VALUES \
//(?,?,?,?,?,?,?,?);");
//        pPreparedStatement->setInt(i++, Player.m_nUserId);
//    }
//    else
//    {
//        pPreparedStatement = pCSqlConnector->prepare("INSERT INTO `Players` \
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
//}


//SPlayer SPlayer::findPlayerById(CSqlConnector* pCSqlConnector, int nId)
//{
//    qDebug() << __FUNCTION__;
//    SPlayer Result;
//    sql::PreparedStatement* pPreparedStatement = pCSqlConnector->prepare("\
//select Players.id, \
//Players.fk_Users_id, \
//Players.name, \
//Players.surname, \
//Players.patronymic, \
//Players.nick, \
//Players.birth_date, \
//Players.quenta, \
//Players.admin \
//from Players \
//where Players.id = ?;");
//    unsigned short i = 1;
//    pPreparedStatement->setInt(i++, nId);
//    sql::ResultSet* pResult = pPreparedStatement->executeQuery();
//    while (pResult->next()) {
//        Result = SPlayer(
//                    pResult->getInt("id"),
//                    pResult->getInt("fk_Users_id"),
//                    pResult->getString("name").c_str(),
//                    pResult->getString("surname").c_str(),
//                    pResult->getString("patronymic").c_str(),
//                    pResult->getString("nick").c_str(),
//                    pResult->getString("birth_date").c_str(),
//                    pResult->getString("quenta").c_str(),
//                    (bool)pResult->getInt("admin")
//        );
//    }
//    delete pResult;
//    delete pPreparedStatement;
//    return Result;
//}

///// <-- Queries
/////////////////////////////////////////////////////////////////////////
/// JSON -->

QJsonObject SPlayer::getJsonObject()
{

    QJsonObject jPlayer;

    jPlayer.insert("Id", m_nId);
    jPlayer.insert("UserId", m_nUserId);
    jPlayer.insert("Name",m_sName.c_str());
    jPlayer.insert("Surname",m_sSurname.c_str());
    jPlayer.insert("Patronymic",m_sPatronymic.c_str());
    jPlayer.insert("Nick",m_sNick.c_str());
    jPlayer.insert("BirthDate",m_sBirthDate.c_str());
    jPlayer.insert("Quenta",m_sQuenta.c_str());
    jPlayer.insert("Admin",m_bAdmin);

    return jPlayer;
}

SPlayer SPlayer::getObjectFromJson(QByteArray jPlayer)
{
    qDebug() << __FUNCTION__;
    QJsonParseError jError;
    QJsonDocument jDocument = QJsonDocument::fromJson(jPlayer, &jError);
    if(jError.error != QJsonParseError::NoError
            || !jDocument.isObject())
    {
        qDebug() << "parse error";
        return SPlayer();
    }
    QJsonObject jNewPlayer = jDocument.object();
    if(!jNewPlayer.contains("Name")
            || !jNewPlayer.contains("Surname")
            || !jNewPlayer.contains("Patronymic")
            || !jNewPlayer.contains("Nick")
            || !jNewPlayer.contains("BirthDate")
            || !jNewPlayer.contains("Quenta")
            || !jNewPlayer.contains("Admin"))
    {
        qDebug() << "not enough fields";
        return SPlayer();
    }
    QJsonValue jName = jNewPlayer.take("Name");
    QJsonValue jSurname = jNewPlayer.take("Surname");
    QJsonValue jPatronymic = jNewPlayer.take("Patronymic");
    QJsonValue jNick = jNewPlayer.take("Nick");
    QJsonValue jBirthDate = jNewPlayer.take("BirthDate");
    QJsonValue jQuenta = jNewPlayer.take("Quenta");
    QJsonValue jAdmin = jNewPlayer.take("Admin");
    if(!jName.isString()
            || !jSurname.isString()
            || !jPatronymic.isString()
            || !jNick.isString()
            || !jBirthDate.isString()
            || !jQuenta.isString()
            || !jAdmin.isBool())
    {
        qDebug() << "wrong type";
        return SPlayer();
    }
    std::string sName = jName.toString().toStdString();
    std::string sSurname = jSurname.toString().toStdString();
    std::string sPatronymic = jPatronymic.toString().toStdString();
    std::string sNick = jNick.toString().toStdString();
    std::string sBirthDate = jBirthDate.toString("2080-01-01").toStdString();
    std::string sQuenta = jQuenta.toString().toStdString();
    bool bAdmin = jAdmin.toBool();
    if(jNewPlayer.contains("Id")
            && jNewPlayer.contains("UserId"))
    {
        QJsonValue jUserId = jNewPlayer.take("UserId");
        QJsonValue jId = jNewPlayer.take("Id");
        if(jId.isDouble()
                && jUserId.isDouble())
        {
            int nId = jId.toInt();
            int nUserId = jUserId.toInt();
            qDebug() << "Id detected" << nId;
            return SPlayer(nId,
                       nUserId,
                       sName,
                       sSurname,
                       sPatronymic,
                       sNick,
                       sBirthDate,
                       sQuenta,
                       bAdmin);
        }
    }
    qDebug() << "No id detected";
    return SPlayer(sName,
               sSurname,
               sPatronymic,
               sNick,
               sBirthDate,
               sQuenta,
               bAdmin);
}

