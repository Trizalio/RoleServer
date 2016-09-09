#ifndef SCREDENTIAL
#define SCREDENTIAL

#include "cjsonserializable.h"
#include <QCryptographicHash>
#include <QDebug>

#define CREDENTIAL_DROP_SCRIPT "DROP TABLE IF EXISTS `Credentials`;"
#define CREDENTIAL_CREATE_SCRIPT "CREATE TABLE `Credentials` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`login` VARCHAR(50) NOT NULL, \
`passwordHash` VARCHAR(128) NOT NULL, \
PRIMARY KEY (`id`) \
);"

#define CREDENTIAL_CONNECT_SCRIPT "ALTER TABLE `Credentials` ADD FOREIGN KEY (id) REFERENCES `Players` (`id`);"
#define CREDENTIAL_UTF8_SCRIPT "ALTER TABLE `Credentials` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"


struct SCredential
{
public:
    static QString getPassHash(QString sPassword);
    SCredential();
    SCredential(int nPlayerId,
            QString sLogin,
            QString sPasswordHash);

    static SCredential getObjectFromJson(QByteArray jCredential);

    int m_nId = 0;
    QString m_sLogin;
    QString m_sPasswordHash;
};

#endif // SCREDENTIAL

