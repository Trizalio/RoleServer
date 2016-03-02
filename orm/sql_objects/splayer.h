#ifndef SPLAYER
#define SPLAYER

#include "cjsonserializable.h"

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
PRIMARY KEY (`id`), \
KEY (`fk_Users_id`) \
);"

#define PLAYER_CONNECT_SCRIPT "ALTER TABLE `Players` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);"
#define PLAYER_UTF8_SCRIPT "ALTER TABLE `Players` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


struct SPlayer : public CJsonSerializable
{
public:
    SPlayer();
    SPlayer(std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta,
            bool bAdmin);
    SPlayer(int nUserId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta,
            bool bAdmin);
    SPlayer(int nId,
            int nUserId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta,
            bool bAdmin);

    QJsonObject getJsonObject() override;

    int m_nId = 0;
    int m_nUserId = 0;

    std::string m_sName;
    std::string m_sSurname;
    std::string m_sPatronymic;
    std::string m_sNick;

    std::string m_sBirthDate;

    std::string m_sQuenta;

    bool m_bAdmin = false;
};

#endif // SPLAYER

