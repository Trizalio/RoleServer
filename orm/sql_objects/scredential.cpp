#include "scredential.h"

#define SALT "Trizalio"

QString SCredential::getPassHash(QString sPassword)
{
    QString sPassWithSalt(sPassword);
    sPassWithSalt.append(SALT);
    qDebug() << sPassWithSalt;
    QString sHash = QCryptographicHash::hash(sPassWithSalt.toLatin1(), QCryptographicHash::Md5).toHex();
    qDebug() << sHash;
    return sHash;
}

SCredential::SCredential(){}

SCredential::SCredential(int nPlayerId, QString sLogin, QString sPasswordHash):
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
    QString sLogin = jLogin.toString();
    QString sPassword = jPassword.toString();
    return SCredential(nPlayerId, sLogin, sPassword);
}
