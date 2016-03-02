#ifndef CNEWS_H
#define CNEWS_H

#include "orm/sql_objects/suser.h"
#include "orm/sql_objects/sgroup.h"
#include "orm/sql_objects/snews.h"

class CNews : public CJsonSerializable
{
public:
    CNews(SNews& News);

    void addAuthor(SUser Author);
    void addGroup(SGroup Group);

    QJsonObject getJsonObject() override;

private:
    SNews m_News;
    SUser m_Author;
    SGroup m_Group;
};

#endif // CNEWS_H
