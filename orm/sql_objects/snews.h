#ifndef SNEWS_H
#define SNEWS_H

#include "cjsonserializable.h"

#define NEWS_DROP_SCRIPT "DROP TABLE IF EXISTS `News`;"
#define NEWS_CREATE_SCRIPT "CREATE TABLE `News` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Roles_id` INTEGER NOT NULL, \
`created` DATETIME NOT NULL, \
`subject` VARCHAR(200) NOT NULL, \
`text` MEDIUMTEXT NOT NULL, \
`anonymously` TINYINT NOT NULL, \
`shared` TINYINT NOT NULL, \
PRIMARY KEY (`id`), \
KEY (`fk_Roles_id`) \
);"

#define NEWS_CONNECT_SCRIPT "ALTER TABLE `News` ADD FOREIGN KEY (fk_Roles_id) REFERENCES `Roles` (`id`);"
#define NEWS_UTF8_SCRIPT "ALTER TABLE `News` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

class SNews : public CJsonSerializable
{
public:
    SNews();

    SNews(int nId,
            int nRoleId,
            QString sCreatedDatetime,
            QString sSubject,
            QString sText,
            bool bAnonymously,
            bool bShared);

    SNews(int nRoleId,
            QString sCreatedDatetime,
            QString sSubject,
            QString sText,
            bool bAnonymously,
            bool bShared);


    QJsonObject getJsonObject() override;

    int m_nId = 0;
    int m_nRoleId = 0;
    QString m_sCreatedDatetime;
    QString m_sSubject;
    QString m_sText;
    bool m_bAnonymously = false;
    bool m_bShared = false;

};

#endif // SNEWS_H
