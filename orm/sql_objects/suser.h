#ifndef SUSER_H
#define SUSER_H

#include <QDebug>

#include "cjsonserializable.h"

#define USER_DROP_SCRIPT "DROP TABLE IF EXISTS `Users`;"
//#define USER_CREATE_SCRIPT "CREATE TABLE `Users` ( \
//`id` INTEGER NOT NULL AUTO_INCREMENT, \
//`name` VARCHAR(50) NOT NULL, \
//`surname` VARCHAR(50) NOT NULL, \
//`patronymic` VARCHAR(50) NOT NULL, \
//`birth_date` DATE NOT NULL, \
//`profession` VARCHAR(50) NOT NULL, \
//`description` MEDIUMTEXT NOT NULL, \
//`deleted` TINYINT NOT NULL DEFAULT 0, \
//`HpMax` INTEGER NOT NULL, \
//`Hp` INTEGER NOT NULL, \
//`MpMax` INTEGER NOT NULL, \
//`Mp` INTEGER NOT NULL, \
//`Air` INTEGER NULL DEFAULT NULL, \
//`hash` VARCHAR NULL DEFAULT NULL, \
//`action_hash` VARCHAR NULL DEFAULT NULL, \
//PRIMARY KEY (`id`), \
//KEY (`hash`) \
//);"

#define USER_CREATE_SCRIPT "CREATE TABLE `Users` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`name` VARCHAR(50) NOT NULL, \
`surname` VARCHAR(50) NOT NULL, \
`patronymic` VARCHAR(50) NOT NULL, \
`male` TINYINT NOT NULL, \
`birth_date` DATE NOT NULL, \
`specialty` VARCHAR(50) NOT NULL, \
`profession` VARCHAR(50) NOT NULL, \
`description` MEDIUMTEXT NOT NULL, \
`hash` VARCHAR(4) NULL DEFAULT NULL, \
`action_hash` VARCHAR(4) NULL DEFAULT NULL, \
`deleted` TINYINT NOT NULL DEFAULT 0, \
PRIMARY KEY (`id`), \
KEY (`hash`) \
);"

#define MALE true
#define FEMALE false

#define USER_CONNECT_SCRIPT "ALTER TABLE `Users` ADD FOREIGN KEY (fk_Hashs_id) REFERENCES `Hashs` (`id`);"
#define USER_UTF8_SCRIPT "ALTER TABLE `Users` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SUser : public CJsonSerializable
{
public:
    SUser();

    SUser(std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            bool bMale,
            std::string sBirthDate,
            std::string sSpecialty,
            std::string sProfession,
            std::string sDescription);

    SUser(int nId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            bool bMale,
            std::string sBirthDate,
            std::string sSpecialty,
            std::string sProfession,
            std::string sDescription);

    QJsonObject getJsonObject() override;
    static SUser getObjectFromJson(QByteArray jUser);

    int m_nId = 0;

    std::string m_sName;
    std::string m_sSurname;
    std::string m_sPatronymic;

    bool m_bMale;

    std::string m_sBirthDate;
    std::string m_sSpecialty;
    std::string m_sProfession;
    std::string m_sDescription;
};

#endif // SUSER_H
