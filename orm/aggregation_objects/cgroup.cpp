#include "cgroup.h"

CGroup::CGroup(SGroup Group):
    m_Group(Group)
{

}

void CGroup::addUser(SUser User)
{
    m_aUsers.push_back(User);

}

QJsonObject CGroup::getJsonObject()
{
    QJsonObject jGroup = m_Group.getJsonObject();

    QJsonArray jUsersArray;
    for(size_t i = 0; i < m_aUsers.size(); ++i)
    {
        QJsonValue jGroupValue(m_aUsers.at(i).getJsonObject());
        jUsersArray.append(jGroupValue);

    }
    QJsonValue jGroupsValue(jUsersArray);
    jGroup.insert("Users", jGroupsValue);

    return jGroup;
}

