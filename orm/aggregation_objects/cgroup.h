#ifndef CGROUP_H
#define CGROUP_H

#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/srole.h"
#include "orm/sql_objects/sgroup.h"

class CGroup : public CJsonSerializable
{
public:
    CGroup();
    CGroup(SGroup Group);

    void addUser(SUser User);

    QJsonObject getJsonObject() override;

private:
    std::vector<SUser> m_aUsers;
    SGroup m_Group;
};

#endif // CGROUP_H
