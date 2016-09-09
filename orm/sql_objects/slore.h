#ifndef SLORE_H
#define SLORE_H

#include "cjsonserializable.h"

#define LORE_DROP_SCRIPT "DROP TABLE IF EXISTS `Lore`;"
#define LORE_CREATE_SCRIPT "CREATE TABLE `Lore` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`title` TEXT NOT NULL, \
`text` MEDIUMTEXT NOT NULL, \
PRIMARY KEY (`id`) \
);"

#define LORE_UTF8_SCRIPT "ALTER TABLE `Lore` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


class SLore : public CJsonSerializable
{
public:
    SLore();
    SLore(QString sTitle, QString sText);
    SLore(int nId, QString sTitle, QString sText);

    QJsonObject getJsonObject() override;

    int m_nId = 0;
    QString m_sTitle;
    QString m_sText;
};

#endif // SLORE_H
