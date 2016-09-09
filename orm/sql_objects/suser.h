#ifndef SUSER_H
#define SUSER_H

#include <QDebug>

#include "cjsonserializable.h"

#define USER_DROP_SCRIPT "DROP TABLE IF EXISTS `Users`;"

#define USER_CREATE_SCRIPT "CREATE TABLE `Users` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`name` VARCHAR(50) NOT NULL, \
`surname` VARCHAR(50) NOT NULL, \
`patronymic` VARCHAR(50) NOT NULL, \
`male` TINYINT NOT NULL, \
`birth_date` DATE NOT NULL, \
`specialty` VARCHAR(150) NOT NULL, \
`profession` VARCHAR(150) NOT NULL, \
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

    SUser(QString sName,
            QString sPatronymic,
            QString sSurname,
            bool bMale,
            QString sBirthDate,
            QString sSpecialty,
            QString sProfession,
            QString sDescription);

    SUser(int nId,
            QString sName,
            QString sSurname,
            QString sPatronymic,
            bool bMale,
            QString sBirthDate,
            QString sSpecialty,
            QString sProfession,
            QString sDescription);

    QJsonObject getJsonObject() override;
    static SUser getObjectFromJson(QByteArray jUser);

    int m_nId = 0;

    QString m_sName;
    QString m_sSurname;
    QString m_sPatronymic;

    bool m_bMale;

    QString m_sBirthDate;
    QString m_sSpecialty;
    QString m_sProfession;
    QString m_sDescription;
};

#endif // SUSER_H
