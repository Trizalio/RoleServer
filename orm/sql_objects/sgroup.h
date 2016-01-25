#ifndef SGROUP
#define SGROUP

#include <string>

#define GROUP_DROP_SCRIPT "DROP TABLE IF EXISTS `Groups`;"
#define GROUP_CREATE_SCRIPT "CREATE TABLE `Groups` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Groups_id_parent` INTEGER NULL DEFAULT NULL, \
`name` VARCHAR(100) NOT NULL, \
`description` MEDIUMTEXT NOT NULL, \
`type` ENUM('Group', 'Project', 'Task', 'Lab') NOT NULL, \
PRIMARY KEY (`id`), \
KEY (`fk_Groups_id_parent`) \
);"

#define GROUP_CONNECT_SCRIPT "ALTER TABLE `Groups` ADD FOREIGN KEY (fk_Groups_id_parent) REFERENCES `Groups` (`id`)"
#define GROUP_UTF8_SCRIPT "ALTER TABLE `Groups` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SGroup
{
public:
    enum Type{
        GROUP,
        PROJECT,
        TASK,
        LAB
    };
    SGroup(){}
    SGroup(int nId,
           int nParentId,
           std::string sName,
           std::string sDescription,
           std::string sType):
        m_nId(nId),
        m_nParentId(nParentId),
        m_sName(sName),
        m_sDescription(sDescription)
    {
        if(sType == "Group")
        {
            m_eType = SGroup::GROUP;
        }
        else if(sType == "Project")
        {
            m_eType = SGroup::PROJECT;
        }
        else if(sType == "Task")
        {
            m_eType = SGroup::TASK;
        }
        else if(sType == "Lab")
        {
            m_eType = SGroup::LAB;
        }

    }
    SGroup(int nParentId,
           std::string sName,
           std::string sDescription,
           Type eType):
        m_nParentId(nParentId),
        m_sName(sName),
        m_sDescription(sDescription),
        m_eType(eType)
    {}

    int m_nId = 0;
    int m_nParentId = 0;
    std::string m_sName;
    std::string m_sDescription;
    Type m_eType = GROUP;
};

#endif // SGROUP

