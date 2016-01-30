#ifndef SGROUP
#define SGROUP

#include "cjsonserializable.h"

#define GROUP_DROP_SCRIPT "DROP TABLE IF EXISTS `Groups`;"
#define GROUP_CREATE_SCRIPT "CREATE TABLE `Groups` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Groups_id_parent` INTEGER NULL DEFAULT NULL, \
`name` VARCHAR(100) NOT NULL, \
`description` MEDIUMTEXT NOT NULL, \
`type` ENUM('hidden', 'normal', 'public', 'lab') NOT NULL, \
PRIMARY KEY (`id`), \
KEY (`fk_Groups_id_parent`) \
);"

#define GROUP_CONNECT_SCRIPT "ALTER TABLE `Groups` ADD FOREIGN KEY (fk_Groups_id_parent) REFERENCES `Groups` (`id`)"
#define GROUP_UTF8_SCRIPT "ALTER TABLE `Groups` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SGroup : public CJsonSerializable
{
public:
    enum eGroupType{
        HIDDEN,
        NORMAL,
        PUBLIC,
        LAB
    };
    static std::string typeToString(eGroupType eType);
    static eGroupType stringToType(std::string sType);
    SGroup();

    SGroup(int nId,
           int nParentId,
           std::string sName,
           std::string sDescription,
           std::string sType);

    SGroup(int nParentId,
           std::string sName,
           std::string sDescription,
           eGroupType eGroupType);

    QJsonObject getJsonObject() override;

    int m_nId = 0;
    int m_nParentId = 0;
    std::string m_sName;
    std::string m_sDescription;
    eGroupType m_eType = HIDDEN;
};

#endif // SGROUP

