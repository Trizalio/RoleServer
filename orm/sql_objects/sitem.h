#ifndef SITEM_H
#define SITEM_H

#include "cjsonserializable.h"

#define ITEM_DROP_SCRIPT "DROP TABLE IF EXISTS `Items`;"
#define ITEM_CREATE_SCRIPT "CREATE TABLE `Items` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`json_data` MEDIUMTEXT NOT NULL, \
`hash` VARCHAR(4) NULL DEFAULT NULL, \
PRIMARY KEY (`id`), \
KEY (`hash`) \
);"

#define ITEM_UTF8_SCRIPT "ALTER TABLE `Items` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


class SItem : public CJsonSerializable
{
public:
    SItem();
    SItem(std::string sJsonData);
    SItem(int m_nId,
          std::string sJsonData,
          std::string sHash);

    QJsonObject getJsonObject() override;

    int m_nId = 0;
    std::string m_sJsonData;
    std::string m_sHash;
};

#endif // SITEM_H
