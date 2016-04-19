#include "scredential.h"

#define SALT "Trizalio"

std::string SCredential::getPassHash(std::string sPassword)
{
    std::string sPassWithSalt(sPassword);
    sPassWithSalt.append(SALT);
    qDebug() << sPassWithSalt.c_str();
    QString sHash = QCryptographicHash::hash(sPassWithSalt.c_str(), QCryptographicHash::Md5).toHex();
    qDebug() << sHash.toStdString().c_str();
    return sHash.toStdString();
}

SCredential::SCredential(){}

SCredential::SCredential(int nPlayerId, std::string sLogin, std::string sPasswordHash):
    m_nId(nPlayerId),
    m_sLogin(sLogin),
    m_sPasswordHash(sPasswordHash)
{}

SCredential SCredential::getObjectFromJson(QByteArray jCredential)
{
    qDebug() << __FUNCTION__;
    QJsonParseError jError;
    QJsonDocument jDocument = QJsonDocument::fromJson(jCredential, &jError);
    if(jError.error != QJsonParseError::NoError
            || !jDocument.isObject())
    {
        qDebug() << "parse error";
        return SCredential();
    }
    QJsonObject jNewCredential = jDocument.object();
    if(!jNewCredential.contains("PlayerId")
            || !jNewCredential.contains("Login")
            || !jNewCredential.contains("Password"))
    {
        qDebug() << "not enough fields";
        return SCredential();
    }
    QJsonValue jPlayerId = jNewCredential.take("PlayerId");
    QJsonValue jLogin = jNewCredential.take("Login");
    QJsonValue jPassword = jNewCredential.take("Password");
    if(!jPlayerId.isDouble()
            || !jLogin.isString()
            || !jPassword.isString())
    {
        qDebug() << "wrong type";
        return SCredential();
    }
    int nPlayerId = jPlayerId.toInt();
    std::string sLogin = jLogin.toString().toStdString();
    std::string sPassword = jPassword.toString().toStdString();
    return SCredential(nPlayerId, sLogin, sPassword);
}
