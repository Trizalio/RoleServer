#include "cuser.h"

CUser::CUser()
{

}

CUser::CUser(SUser User):
    m_User(User)
{

}

void CUser::addGroup(SGroup Group)
{
    m_aGroups.push_back(Group);
}

QJsonObject CUser::getJsonObject()
{
    QJsonObject jUser = m_User.getJsonObject();
    QJsonArray jGroupsArray;
    for(size_t i = 0; i < m_aGroups.size(); ++i)
    {
        QJsonValue jGroupValue(m_aGroups.at(i).getJsonObject());
        jGroupsArray.append(jGroupValue);
    }
    QJsonValue jGroupsValue(jGroupsArray);
    jUser.insert("Groups", jGroupsValue);

    return jUser;
}

//QByteArray CUser::getJson()
//{
//    QJsonObject jUser;

//    QJsonArray jGroupsArray;
//    for(size_t i = 0; i < m_aGroups.size(); ++i)
//    {
//        QJsonObject jCellObject;
//        jCellObject.insert("Id", QJsonValue(m_aGroups.at(i).m_nId));
//        jCellObject.insert("Name", QJsonValue(m_aGroups.at(i).m_sName));
//        jCellObject.insert("Description", QJsonValue(m_aGroups.at(i).m_sDescription));

//        QJsonValue jGroupValue(jCellObject);
//        jGroupsArray.append(jGroupValue);

//    }
//    QJsonValue jGroupsValue(jGroupsArray);
//    jUser.insert("Groups", jGroupsValue);

//    jUser.insert("Id", m_nId);
//    jUser.insert("Name", m_sName);
//    jUser.insert("Surname", m_sSurname);
//    jUser.insert("Patronymic", m_sPatronymic);
//    jUser.insert("BirthDate", m_sBirthDate);
//    jUser.insert("Profession", m_sProfession);
//    jUser.insert("Description", m_sDescription);


//    QJsonDocument jDocument;
//    jDocument.setObject(jUser);
//    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

//    return aJson;
//}

