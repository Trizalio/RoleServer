#include "cgroup.h"

CGroup::CGroup()
{

}

CGroup::CGroup(SGroup Group):
    m_Group(Group)
{

}

void CGroup::addUser(SUser User)
{
    m_aUsers.push_back(User);

}

void CGroup::setNews(std::vector<CNews> aNews)
{
    m_aNews = aNews;
}

QJsonObject CGroup::getJsonObject()
{
    QJsonObject jGroup = m_Group.getJsonObject();

    QJsonArray jUsersArray;
    for(size_t i = 0; i < m_aUsers.size(); ++i)
    {
        QJsonValue jUserValue(m_aUsers.at(i).getJsonObject());
        jUsersArray.append(jUserValue);

    }
    QJsonValue jUsersValue(jUsersArray);
    jGroup.insert("Users", jUsersValue);


    QJsonArray jNewsArray;
    for(size_t i = 0; i < m_aNews.size(); ++i)
    {
        QJsonValue jNewsValue(m_aNews.at(i).getJsonObject());
        jNewsArray.append(jNewsValue);

    }
    QJsonValue jNewsArValue(jNewsArray);
    jGroup.insert("News", jNewsArValue);

    return jGroup;
}

bool CGroup::notEmpty()
{

    qDebug() << __FUNCTION__ << bool(m_Group.m_nId);
    return bool(m_Group.m_nId);
}

