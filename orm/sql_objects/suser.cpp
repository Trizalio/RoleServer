#include "suser.h"



SUser::SUser(){}

SUser::SUser(std::string sName, std::string sSurname, std::string sPatronymic, bool bMale, std::string sBirthDate, std::string sSpecialty, std::string sProfession, std::string sDescription):
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),

    m_bMale(bMale),

    m_sBirthDate(sBirthDate),
    m_sProfession(sProfession),
    m_sSpecialty(sSpecialty),
    m_sDescription(sDescription)
{}

SUser::SUser(int nId, std::string sName, std::string sSurname, std::string sPatronymic, bool bMale, std::string sBirthDate, std::string sSpecialty, std::string sProfession, std::string sDescription):
    m_nId(nId),

    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),

    m_bMale(bMale),

    m_sBirthDate(sBirthDate),
    m_sSpecialty(sSpecialty),
    m_sProfession(sProfession),
    m_sDescription(sDescription)
{}


QJsonObject SUser::getJsonObject()
{
    QJsonObject jUser;

    jUser.insert("Id", m_nId);
    jUser.insert("Name",m_sName.c_str());
    jUser.insert("Surname",m_sSurname.c_str());
    jUser.insert("Male",m_bMale);
    jUser.insert("Patronymic",m_sPatronymic.c_str());
    jUser.insert("BirthDate",m_sBirthDate.c_str());
    jUser.insert("Specialty",m_sSpecialty.c_str());
    jUser.insert("Profession",m_sProfession.c_str());
    jUser.insert("Description",m_sDescription.c_str());

//    QJsonValue jId = jUser.take("Id");
//    int nId = jId.toInt();
//    qDebug() << m_nId << "Id read from serialize" << jId.toInt() << jId.toDouble() << jId.toString() << jId.toVariant();

    return jUser;
}

SUser SUser::getObjectFromJson(QByteArray jUser)
{
    qDebug() << __FUNCTION__;
    QJsonParseError jError;
    QJsonDocument jDocument = QJsonDocument::fromJson(jUser, &jError);
    if(jError.error != QJsonParseError::NoError
            || !jDocument.isObject())
    {
        qDebug() << "parse error";
        return SUser();
    }
    QJsonObject jNewUser = jDocument.object();
    if(!jNewUser.contains("Name")
            || !jNewUser.contains("Surname")
            || !jNewUser.contains("Patronymic")
            || !jNewUser.contains("Male")
            || !jNewUser.contains("BirthDate")
            || !jNewUser.contains("Specialty")
            || !jNewUser.contains("Profession")
            || !jNewUser.contains("Description"))
    {
        qDebug() << "not enough fields";
        return SUser();
    }
    QJsonValue jName = jNewUser.take("Name");
    QJsonValue jSurname = jNewUser.take("Surname");
    QJsonValue jPatronymic = jNewUser.take("Patronymic");
    QJsonValue jMale = jNewUser.take("Male");
    QJsonValue jBirthDate = jNewUser.take("BirthDate");
    QJsonValue jSpecialty = jNewUser.take("Specialty");
    QJsonValue jProfession = jNewUser.take("Profession");
    QJsonValue jDescription = jNewUser.take("Description");
    if(!jName.isString()
            || !jSurname.isString()
            || !jPatronymic.isString()
            || !jMale.isBool()
            || !jBirthDate.isString()
            || !jSpecialty.isString()
            || !jProfession.isString()
            || !jDescription.isString())
    {
        qDebug() << "wrong type";
        return SUser();
    }
    std::string sName = jName.toString().toStdString();
    std::string sSurname = jSurname.toString().toStdString();
    std::string sPatronymic = jPatronymic.toString().toStdString();
    bool bMale = jMale.toBool();
    std::string sBirthDate = jBirthDate.toString("2080-01-01").toStdString();
    std::string sSpecialty = jSpecialty.toString().toStdString();
    std::string sProfession = jProfession.toString().toStdString();
    std::string sDescription = jDescription.toString().toStdString();
    if(jNewUser.contains("Id"))
    {
        QJsonValue jId = jNewUser.take("Id");
        if(jId.isDouble())
        {
            int nId = jId.toInt();
            qDebug() << "Id detected" << nId;
            return SUser(nId,
                        sName,
                        sSurname,
                        sPatronymic,
                        bMale,
                        sBirthDate,
                        sSpecialty,
                        sProfession,
                        sDescription);
        }
    }
    qDebug() << "No id detected";
    return SUser(sName,
               sSurname,
               sPatronymic,
               bMale,
               sBirthDate,
               sSpecialty,
               sProfession,
               sDescription);
}
