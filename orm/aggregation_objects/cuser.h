#ifndef CUSER_H
#define CUSER_H

#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/srole.h"
#include "orm/sql_objects/sgroup.h"

class CUser : public CJsonSerializable
{
public:
    CUser(SUser User);

    void addGroup(SGroup Group);

    QJsonObject getJsonObject() override;

private:
    std::vector<SGroup> m_aGroups;
    SUser m_User;

};

#endif // CUSER_H
