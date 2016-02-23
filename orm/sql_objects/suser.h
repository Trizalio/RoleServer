#ifndef SUSER_H
#define SUSER_H

#include <QDebug>

#include "cjsonserializable.h"

#define USER_DROP_SCRIPT "DROP TABLE IF EXISTS `Users`;"
#define USER_CREATE_SCRIPT "CREATE TABLE `Users` (\
`id` INTEGER NOT NULL AUTO_INCREMENT,\
`name` VARCHAR(50) NOT NULL,\
`surname` VARCHAR(50) NOT NULL,\
`patronymic` VARCHAR(50) NOT NULL,\
`birth_date` DATE NOT NULL,\
`profession` VARCHAR(50) NOT NULL,\
`description` MEDIUMTEXT NOT NULL,\
PRIMARY KEY (`id`)\
);"

#define USER_UTF8_SCRIPT "ALTER TABLE `Users` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SUser : public CJsonSerializable
{
public:
    SUser();

    SUser(std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sBirthDate,
            std::string sProfession,
            std::string sDescription);

    SUser(int nId,
            std::string sName,
            std::string sSurname,
            std::string sPatronymic,
            std::string sBirthDate,
            std::string sProfession,
            std::string sDescription);

    QJsonObject getJsonObject() override;
    static SUser getObjectFromJson(QByteArray jUser);

    int m_nId = 0;
    std::string m_sName;
    std::string m_sSurname;
    std::string m_sPatronymic;
    std::string m_sBirthDate;
    std::string m_sProfession;
    std::string m_sDescription;
};

#endif // SUSER_H
