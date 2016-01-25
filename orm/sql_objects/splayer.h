#ifndef SPLAYER
#define SPLAYER

#include <string>

#define PLAYER_DROP_SCRIPT "DROP TABLE IF EXISTS `Players`;"
#define PLAYER_CREATE_SCRIPT "CREATE TABLE `Players` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Users_id` INTEGER NOT NULL, \
`name` VARCHAR(50) NOT NULL, \
`surname` VARCHAR(50) NOT NULL, \
`patronymic` VARCHAR(50) NOT NULL, \
`nick` VARCHAR(50) NOT NULL, \
`birth_date` DATE NOT NULL, \
`quenta` MEDIUMTEXT NOT NULL, \
PRIMARY KEY (`id`), \
KEY (`fk_Users_id`) \
);"

//ALTER TABLE `Players` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);
#define PLAYER_CONNECT_SCRIPT "ALTER TABLE `Players` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);"
#define PLAYER_UTF8_SCRIPT "ALTER TABLE `Players` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


struct SPlayer
{
public:
    SPlayer(){}
    SPlayer(std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta):
        m_sName(sName),
        m_sSurname(sSurname),
        m_sPatronymic(sPatronymic),
        m_sNick(sNick),
        m_sBirthDate(sBirthDate),
        m_sQuenta(sQuenta)
    {}
    SPlayer(int nUserId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta):
        m_nUserId(nUserId),
        m_sName(sName),
        m_sSurname(sSurname),
        m_sPatronymic(sPatronymic),
        m_sNick(sNick),
        m_sBirthDate(sBirthDate),
        m_sQuenta(sQuenta)
    {}
    SPlayer(int nId,
            int nUserId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sNick,
            std::string sBirthDate,
            std::string sQuenta):
        m_nId(nId),
        m_nUserId(nUserId),
        m_sName(sName),
        m_sSurname(sSurname),
        m_sPatronymic(sPatronymic),
        m_sNick(sNick),
        m_sBirthDate(sBirthDate),
        m_sQuenta(sQuenta)
    {}

    int m_nId = 0;
    int m_nUserId = 0;

    std::string m_sName;
    std::string m_sSurname;
    std::string m_sPatronymic;
    std::string m_sNick;

    std::string m_sBirthDate;

    std::string m_sQuenta;
};

#endif // SPLAYER

