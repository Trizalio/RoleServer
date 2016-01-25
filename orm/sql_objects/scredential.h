#ifndef SCREDENTIAL
#define SCREDENTIAL

#include <string>

#define CREDENTIAL_DROP_SCRIPT "DROP TABLE IF EXISTS `Credentials`;"
#define CREDENTIAL_CREATE_SCRIPT "CREATE TABLE `Credentials` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`login` VARCHAR(50) NOT NULL, \
`passwordHash` VARCHAR(128) NOT NULL, \
PRIMARY KEY (`id`) \
);"

//ALTER TABLE `Credentials` ADD FOREIGN KEY (id) REFERENCES `Players` (`id`);
#define CREDENTIAL_CONNECT_SCRIPT "ALTER TABLE `Credentials` ADD FOREIGN KEY (id) REFERENCES `Players` (`id`);"
#define CREDENTIAL_UTF8_SCRIPT "ALTER TABLE `Credentials` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SCredential
{
public:
    SCredential(){}
//    SCredential(std::string sLogin,
//            std::string sPasswordHash):
//        m_sLogin(sLogin),
//        m_sPasswordHash(sPasswordHash)
//    {}
    SCredential(int nId,
            std::string sLogin,
            std::string sPasswordHash):
        m_nId(nId),
        m_sLogin(sLogin),
        m_sPasswordHash(sPasswordHash)
    {}

    int m_nId = 0;
    std::string m_sLogin;
    std::string m_sPasswordHash;
};

#endif // SCREDENTIAL

