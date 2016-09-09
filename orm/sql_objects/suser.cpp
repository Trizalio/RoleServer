#include "suser.h"



SUser::SUser(){}

SUser::SUser(QString sName, QString sPatronymic, QString sSurname, bool bMale, QString sBirthDate, QString sSpecialty, QString sProfession, QString sDescription):
    m_sName(sName),
    m_sSurname(sSurname),
    m_sPatronymic(sPatronymic),

    m_bMale(bMale),

    m_sBirthDate(sBirthDate),
    m_sProfession(sProfession),
    m_sSpecialty(sSpecialty),
    m_sDescription(sDescription)
{}

SUser::SUser(int nId, QString sName, QString sSurname, QString sPatronymic, bool bMale, QString sBirthDate, QString sSpecialty, QString sProfession, QString sDescription):
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
    jUser.insert("Name",m_sName);
    jUser.insert("Surname",m_sSurname);
    jUser.insert("Male",m_bMale);
    jUser.insert("Patronymic",m_sPatronymic);
    jUser.insert("BirthDate",m_sBirthDate);
    jUser.insert("Specialty",m_sSpecialty);
    jUser.insert("Profession",m_sProfession);
    jUser.insert("Description",m_sDescription);

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
    QString sName = jName.toString();
    QString sSurname = jSurname.toString();
    QString sPatronymic = jPatronymic.toString();
    bool bMale = jMale.toBool();
    QString sBirthDate = jBirthDate.toString("2080-01-01");
    QString sSpecialty = jSpecialty.toString();
    QString sProfession = jProfession.toString();
    QString sDescription = jDescription.toString();
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
