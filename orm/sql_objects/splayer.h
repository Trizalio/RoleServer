#ifndef SPLAYER
#define SPLAYER

#include <QDebug>

#include "cjsonserializable.h"
#include "orm/csqlconnector.h"

#define PLAYER_DROP_SCRIPT "DROP TABLE IF EXISTS `Players`;"
#define PLAYER_CREATE_SCRIPT "CREATE TABLE `Players` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Users_id` INTEGER NULL, \
`name` VARCHAR(50) NOT NULL, \
`surname` VARCHAR(50) NOT NULL, \
`patronymic` VARCHAR(50) NOT NULL, \
`nick` VARCHAR(50) NOT NULL, \
`birth_date` DATE NOT NULL, \
`quenta` MEDIUMTEXT NOT NULL, \
`admin` TINYINT NOT NULL, \
`deleted` TINYINT NOT NULL DEFAULT 0, \
PRIMARY KEY (`id`), \
KEY (`fk_Users_id`) \
);"

#define PLAYER_CONNECT_SCRIPT "ALTER TABLE `Players` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);"
#define PLAYER_UTF8_SCRIPT "ALTER TABLE `Players` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


struct SPlayer : public CJsonSerializable
{
public:
    SPlayer();
    SPlayer(QString sName,
            QString sSurname,
            QString sPatronymic,
            QString sNick,
            QString sBirthDate,
            QString sQuenta,
            bool bAdmin);
    SPlayer(int nUserId,
            QString sName,
            QString sSurname,
            QString sPatronymic,
            QString sNick,
            QString sBirthDate,
            QString sQuenta,
            bool bAdmin);
    SPlayer(int nId,
            int nUserId,
            QString sName,
            QString sSurname,
            QString sPatronymic,
            QString sNick,
            QString sBirthDate,
            QString sQuenta,
            bool bAdmin);

    /// <-- Constructors
    /////////////////////////////////////////////////////////////////////////
//    /// Queries -->

//    static void insertPlayer(CSqlConnector* pCSqlConnector, SPlayer& Player);

//    /// <-- Queries
    /////////////////////////////////////////////////////////////////////////
    /// JSON -->

    QJsonObject getJsonObject() override;
    static SPlayer getObjectFromJson(QByteArray jPlayer);

    /// <-- JSON
    /////////////////////////////////////////////////////////////////////////
    /// Params -->

    int m_nId = 0;
    int m_nUserId = 0;

    QString m_sName;
    QString m_sSurname;
    QString m_sPatronymic;
    QString m_sNick;

    QString m_sBirthDate;

    QString m_sQuenta;

    bool m_bAdmin = false;
};

#endif // SPLAYER

