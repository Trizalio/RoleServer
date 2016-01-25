#ifndef SROLE
#define SROLE

#include <string>

#define ROLE_DROP_SCRIPT "DROP TABLE IF EXISTS `Roles`;"
#define ROLE_CREATE_SCRIPT "CREATE TABLE `Roles` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Users_id` INTEGER NOT NULL, \
`fk_Groups_id` INTEGER NOT NULL, \
`owner` TINYINT NOT NULL, \
PRIMARY KEY (`id`), \
KEY (`fk_Groups_id`), \
KEY (`fk_Users_id`) \
);"

#define ROLE_CONNECT_SCRIPT_1 "ALTER TABLE `Roles` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);"
#define ROLE_CONNECT_SCRIPT_2 "ALTER TABLE `Roles` ADD FOREIGN KEY (fk_Groups_id) REFERENCES `Groups` (`id`);"
#define ROLE_UTF8_SCRIPT "ALTER TABLE `Roles` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SRole
{
public:
    SRole(){}
    SRole(int nId,
          int nUserId,
          int nGroupId,
          bool bOwner):
        m_nId(nId),
        m_nUserId(nUserId),
        m_nGroupId(nGroupId),
        m_bOwner(bOwner)
    {}
    SRole(int nUserId,
          int nGroupId,
          bool bOwner):
        m_nUserId(nUserId),
        m_nGroupId(nGroupId),
        m_bOwner(bOwner)
    {}

    int m_nId = 0;
    int m_nUserId = 0;
    int m_nGroupId = 0;
    bool m_bOwner = false;
};


#endif // SROLE

