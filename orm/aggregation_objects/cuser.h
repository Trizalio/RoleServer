#ifndef CUSER_H
#define CUSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/srole.h"
#include "orm/sql_objects/sgroup.h"

class CUser : public SUser
{
public:
    CUser(SUser User);

    void addGroup(SGroup Group);

    QByteArray getJson();

private:
    std::vector<SGroup> m_aGroups;

};

#endif // CUSER_H
