#include "cnews.h"

CNews::CNews(SNews &News):
    m_News(News)
{

}

void CNews::addAuthor(SUser Author)
{
    m_Author = Author;
}

void CNews::addGroup(SGroup Group)
{
    m_Group = Group;
}

QJsonObject CNews::getJsonObject()
{
    QJsonObject jNews = m_News.getJsonObject();

    QJsonObject jAuthor = m_Author.getJsonObject();
    QJsonValue jAuthorValue(jAuthor);
    jNews.insert("Author", jAuthorValue);

    QJsonObject jGroup = m_Group.getJsonObject();
    QJsonValue jGroupValue(jGroup);
    jNews.insert("Group", jGroupValue);

    return jNews;

}

