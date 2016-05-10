#ifndef SHASH_H
#define SHASH_H

#include "cjsonserializable.h"


#include <QDateTime>
#include <QCryptographicHash>

#define HASH_DROP_SCRIPT "DROP TABLE IF EXISTS `Hashs`;"
#define HASH_CREATE_SCRIPT "CREATE TABLE `Hashs` ( \
`id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL, \
`hash` VARCHAR(32) NOT NULL, \
PRIMARY KEY (`id`) \
);"

#define HASH_UTF8_SCRIPT "ALTER TABLE `Hashs` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

class SHash : public CJsonSerializable
{
public:
    static SHash generateRandomHash();

    SHash();
    SHash(std::string sHash);
    SHash(int nId,
           std::string sHash);

    int m_nId = 0;
    std::string m_sHash;

    QJsonObject getJsonObject() override;

private:
    static int m_nHashsGenerated;
};

#endif // SHASH_H
