#ifndef CGROUP_H
#define CGROUP_H

#include "orm/sql_objects/suser.h"
#include "orm/aggregation_objects/cnews.h"
#include "orm/sql_objects/srole.h"
#include "orm/sql_objects/sgroup.h"

class CGroup : public CJsonSerializable
{
public:
    CGroup();
    CGroup(SGroup Group);

    void addUser(SUser User);
    void setNews(std::vector<CNews> aNews);

    QJsonObject getJsonObject() override;
    bool notEmpty();

private:
    std::vector<SUser> m_aUsers;
    std::vector<CNews> m_aNews;
    SGroup m_Group;
};

#endif // CGROUP_H
